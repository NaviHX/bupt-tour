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

#include "global.h"
#include "MapCanvas.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // 初始化菜单栏
    QMenu *userMenu = menuBar()->addMenu(tr("&User"));
    addOneUser = new QAction(tr("&add one user"), this);
    userMenu->addAction(addOneUser);

    QMenu *timerMenu = menuBar()->addMenu(tr("&Timer"));
    start = new QAction(tr("&Start"), this);
    pause = new QAction(tr("&Pause"), this);
    timerMenu->addAction(start);
    timerMenu->addAction(pause);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    help = new QAction(tr("&Help"), this);
    helpMenu->addAction(help);

    // 初始化计时器
    timer = new QTimer(this);
    timerStatus = false;

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
    console->setFixedSize(950,300);

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
}

void MainWindow::startTimer()
{
    if (!isTimerStart())
    {
        timer->start(TimeInterval * 1000);
        std::cout << "Timer Start\n";
        timerStatus = true;
    }
}

void MainWindow::pauseTimer()
{
    if (isTimerStart())
    {
        timer->stop();
        timerStatus = false;
    }
}

void MainWindow::showHelp()
{
    QDesktopServices::openUrl(QUrl("https://github.com/NaviHX/bupt-tour/blob/master/doc/developer.md"));
}

void MainWindow::addUser()
{
    pauseTimer();
    QStringList tacList;
    tacList<<tr("1. shortest")<<tr("2. congestion")<<tr("3. Bike");
    std::vector<int> plots, tact;
    bool ok = false;
    QString text = QInputDialog::getItem(this, tr("Add User"), tr("Select where to start"), plotList, 0, false, &ok);
    if (!ok)
        return;
    plots.push_back(Id[text.toStdString()]);
    while (true)
    {
        bool ok1=false,ok2=false;
        QString p=QInputDialog::getItem(this,tr("Add User"),tr("Select a destination"),plotList,0,false,&ok1);
        if(!ok1)
            break;
        QString t=QInputDialog::getItem(this,tr("Add User"),tr("Select a tactics"),tacList,0,false,&ok2);
        if(!ok2)
            break;
        QByteArray ba=t.toLatin1();
        char* ch=ba.data();
        plots.push_back(Id[p.toStdString()]);
        tact.push_back(ch[0]-'1');
    }
    std::stack<std::pair<int,int>> st=myTour->getSerialPath(plots,tact);
    ok=false;
    for(int i=0;i<myUsers.size();i++)
    {
        if(myUsers[i]==nullptr)
        {
            myUsers[i]=new User(st);
            ok=true;
            break;
        }
    }
}

void MainWindow::refresh()
{
    for (int i = 0; i < myUsers.size(); i++)
    {
        if (myUsers[i] != nullptr)
        {
            int ret = myUsers[i]->move();
            if (ret == 0)
            {
                delete myUsers[i];
                myUsers[i] = nullptr;
            }
        }
    }
    canvas->repaint();
}

bool MainWindow::isTimerStart()
{
    return timerStatus;
}
