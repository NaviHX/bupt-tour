/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-07
 * @file        : MainWindow.cpp
 * @description : 
*/

#include "MainWindow.h"
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtGui/QDesktopServices>
#include <QtCore/QUrl>
#include <QtWidgets/QLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMessageBox>

#include "global.h"
#include "MapCanvas.h"
#include "settingWnd.h"
#include "Bus.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // 初始化菜单栏
    QMenu *userMenu = menuBar()->addMenu(tr("&User"));
    addOneUser = new QAction(tr("&add one user"), this);
    findNearby = new QAction(tr("&Find nearby locations"), this);
    chDes = new QAction(tr("Change Destination"), this);
    userMenu->addAction(addOneUser);
    userMenu->addAction(findNearby);
    userMenu->addAction(chDes);

    QMenu *timerMenu = menuBar()->addMenu(tr("&Timer"));
    start = new QAction(tr("&Start"), this);
    pause = new QAction(tr("&Pause"), this);
    timerMenu->addAction(start);
    timerMenu->addAction(pause);

    setting = menuBar()->addAction(tr("&Setting"));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    help = new QAction(tr("&Help"), this);
    helpMenu->addAction(help);

    // 初始化计时器
    timer = new QTimer(this);
    timerStatus = false;
    timerCount = 0;

    //  初始化其他成员和全局变量
    myTour = new Tour();
    for (int i = 0; i < BuildingCnt; i++)
    {
        plotList << Building[i].c_str();
    }
    myUsers.resize(3);
    for (int i = 0; i < myUsers.size(); i++)
    {
        myUsers[i] = nullptr;
    }

    // 初始化窗口大小
    this->resize(QSize(1000, 800));

    QWidget *centr = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centr);
    // 初始化绘图区
    canvas = new MapCanvas(this, myUsers);

    // 初始化日志输出区
    console = new QTextEdit(this);
    console->setFixedSize(950, 300);

    layout->addWidget(canvas);
    layout->addWidget(console);

    centr->setLayout(layout);
    this->setCentralWidget(centr);

    // 连接信号槽
    connect(addOneUser, SIGNAL(triggered()), this, SLOT(addUser()));
    connect(timer, &QTimer::timeout, this, &MainWindow::refresh);
    connect(start, SIGNAL(triggered()), this, SLOT(startTimer()));
    connect(pause, SIGNAL(triggered()), this, SLOT(pauseTimer()));
    connect(help, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(findNearby, SIGNAL(triggered()), this, SLOT(findNearbyLoc()));
    connect(chDes, SIGNAL(triggered()), this, SLOT(changeDes()));
    connect(setting, SIGNAL(triggered()), this, SLOT(showSetting()));

    this->printOnCons(tr("Copyright © 2021 BUPT-Tour. All rights reserved."));
}

void MainWindow::startTimer()
{
    if (!isTimerStart())
    {
        timer->start(TimeInterval * 1000);
        this->printOnCons(tr("Timer Start"));
        timerStatus = true;
    }
}

void MainWindow::pauseTimer()
{
    if (isTimerStart())
    {
        timer->stop();
        this->printOnCons(tr("Timer Stop"));
        timerStatus = false;
    }
}

void MainWindow::showHelp()
{
    QDesktopServices::openUrl(QUrl("https://github.com/NaviHX/bupt-tour/blob/master/doc/instruction.md"));
}

void MainWindow::addUser()
{
    pauseTimer();
    QStringList tacList;
    tacList << tr("1. shortest") << tr("2. congestion") << tr("3. Bike");
    std::vector<int> plots, tact;
    bool ok = false;
    QString text = QInputDialog::getItem(this, tr("Add User"), tr("Select where to start"), plotList, 0, false, &ok);
    if (!ok)
        return;
    // plots.push_back(Id[text.toStdString()]);
    plots.push_back(Tour::getId(text.toStdString()));
    while (true)
    {
        bool ok1 = false, ok2 = false;
        QString p = QInputDialog::getItem(this, tr("Add User"), tr("Select a destination"), plotList, 0, false, &ok1);
        if (!ok1)
            break;
        QString t = QInputDialog::getItem(this, tr("Add User"), tr("Select a tactics"), tacList, 0, false, &ok2);
        if (!ok2)
            break;
        QByteArray ba = t.toLatin1();
        char *ch = ba.data();
        // plots.push_back(Id[p.toStdString()]);
        plots.push_back(Tour::getId(p.toStdString()));
        tact.push_back(ch[0] - '1');
    }
    std::stack<std::pair<int, int>> st = myTour->getSerialPath(plots, tact);
    if (st.empty())
    {
        printOnCons(tr("CANNOT ADD USER : NO PLOTS SELECTED"));
        return;
    }
    ok = false;
    for (int i = 0; i < myUsers.size(); i++)
    {
        if (myUsers[i] == nullptr) // 寻找空闲用户指针
        {
            myUsers[i] = new User(st);
            this->printOnCons(tr("User %1 add").arg(QString::number(i)));
            std::string *pathStr = getPathStr(st);
            this->printOnCons(tr("Path : %1").arg(QString::fromStdString(*pathStr)));
            delete pathStr;
            ok = true;
            break;
        }
    }
    if (!ok)
    {
        QMessageBox::information(NULL, tr("Warning"), tr("Cannot add user : no mem"), QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    canvas->repaint();
}

void MainWindow::refresh()
{
    CurTime++;
    if (CurTime >= MAX_TIME)
        CurTime = 0;
    for (int i = 0; i < myUsers.size(); i++)
    {
        if (myUsers[i] != nullptr)
        {
            int ret = myUsers[i]->move();
            if (ret == 0)
            {
                delete myUsers[i];
                myUsers[i] = nullptr;
                this->printOnCons(tr("User %1 arrive at destination").arg(QString::number(i)));
            }
            else if (ret > 1)
            {
                int plotId = ret - 2;
                this->printOnCons(tr("User %1 arrive at %2")
                                      .arg(QString::number(i),
                                           QString::fromStdString(Building[plotId])));
            }
            else if (ret <= -2)
            {
                this->printOnCons(tr("User %1 get on bus %2")
                                      .arg(QString::number(i),
                                           QString::fromStdString(BusArr[abs(ret) - 2]->getName())));
            }
        }
    }
    timerCount++;
    canvas->repaint();
}

bool MainWindow::isTimerStart()
{
    return timerStatus;
}

void MainWindow::printOnCons(const QString &str)
{
    QString timeStamp = tr("[ %1 ] ").arg(QString::number(CurTime));
    if (console->document()->lineCount() > 100)
    {
        console->clear();
    }

    QTextCursor cursor = console->textCursor();
    cursor.movePosition(QTextCursor::End);
    console->setTextCursor(cursor);
    console->insertPlainText(timeStamp + str + '\n');

#ifdef DEBUG

    debugStream << "[" << timerCount << "]"
                << " : " << str << std::endl;

#endif
}

std::string *MainWindow::getPathStr(std::stack<std::pair<int, int>> &st)
{
    std::string *res = new std::string;
    if (st.empty())
    {
        // 防止非法访问内存
        return res;
    }
    (*res) += Building[abs(st.top().first)];
    st.pop();
    while (!st.empty())
    {
        (*res) += "->" + Building[abs(st.top().first)];
        st.pop();
    }
    return res;
}

void MainWindow::findNearbyLoc()
{
    this->pauseTimer();
    bool ok = false;
    for (int i = 0; i < myUsers.size(); i++)
    {
        if (myUsers[i] != nullptr && myUsers[i]->getDes() != INVALID)
        {
            ok = true;
            if (myUsers[i]->getDes() >= 0)
            {
                auto v = myUsers[i]->getSpot();
                this->printOnCons(tr("User %1 nearby locations :").arg(QString::number(i)));
                for (int j = 0; j < v.size(); j++)
                {
                    int l = v[j].first, w = v[j].second;
                    this->printOnCons(tr("%1 : %2 meters")
                                          .arg(
                                              QString::fromStdString(Building[l]),
                                              QString::number(w * 10)));
                }
            }
            else
            {
                this->printOnCons(tr("User %1 is out of the campus").arg(QString::number(i)));
            }
        }
    }
    if (!ok)
    {
        this->printOnCons(tr("No User added"));
    }
}

void MainWindow::changeDes()
{
    this->pauseTimer();
    bool ok = false;
    QStringList uList;
    for (int i = 0; i < myUsers.size(); i++)
    {
        /* 
            不能简单地判断指针是否为空
            合法的可以修改目标的用户，路径栈不能为空
            指针判空仅确保实例未释放
         */
        if (myUsers[i] != nullptr && myUsers[i]->getDes() != INVALID)
        {
            ok = true;
            uList << QString::number(i);
        }
    }
    if (!ok)
    {
        this->printOnCons(tr("No user added"));
        return;
    }
    QString text = QInputDialog::getItem(this, tr("select User"), tr("Select which to change"), uList, 0, false, &ok);
    if (!ok)
        return;
    QByteArray ba = text.toLatin1();
    char *ch = ba.data();
    int u = ch[0] - '0';
    int curDes = myUsers[u]->getDes();
    int interv = myUsers[u]->getInterv();
    int curX = myUsers[u]->getX();
    int curY = myUsers[u]->getY();
    int startPoint = myUsers[u]->getStart();
    int turns = myUsers[u]->getTurns();
    // delete myUsers[u];
    // myUsers[u] = nullptr;

    QStringList tacList;
    tacList << tr("1. shortest") << tr("2. congestion") << tr("3. Bike");
    std::vector<int> plots, tact;
    plots.push_back(curDes);
    while (true)
    {
        bool ok1 = false, ok2 = false;
        QString p = QInputDialog::getItem(this, tr("Add User"), tr("Select a destination"), plotList, 0, false, &ok1);
        if (!ok1)
            break;
        QString t = QInputDialog::getItem(this, tr("Add User"), tr("Select a tactics"), tacList, 0, false, &ok2);
        if (!ok2)
            break;
        QByteArray ba = t.toLatin1();
        char *ch = ba.data();
        // plots.push_back(Id[p.toStdString()]);
        plots.push_back(Tour::getId(p.toStdString()));
        tact.push_back(ch[0] - '1');
    }
    std::stack<std::pair<int, int>> st = myTour->getSerialPath(plots, tact);

    if (st.empty())
    {
        printOnCons(tr("CANNOT CHANGE : NO PLOTS SELECTED"));
        return;
    }
    delete myUsers[u];
    myUsers[u] = nullptr;
    auto pairtemp = st.top();
    st.pop();
    if (st.top().first == startPoint)
    {
        int temp = curDes;
        curDes = startPoint;
        startPoint = temp;

        temp = turns;
        turns = interv;
        interv = temp;
    }
    else
    {
        st.push(pairtemp);
    }
    myUsers[u] = new User(st, curX, curY, curDes, interv, startPoint, turns);

    std::string *pathStr = getPathStr(st);
    this->printOnCons(tr("Path : %1").arg(QString::fromStdString(*pathStr)));
    delete pathStr;
}

void MainWindow::showSetting()
{
    pauseTimer();
    settingWnd *s = new settingWnd;
    s->show();
}
