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
#include "global.h"

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
    // myTour=new Tour();

    // 初始化窗口大小
    this->resize(QSize(800, 600));

    // ToDo : 初始化绘图区

    // ToDo : 初始化日志输出区

    // 连接信号槽
    connect(addOneUser, SIGNAL(triggered()), this, SLOT(addUser()));
    connect(timer, &QTimer::timeout, this, &MainWindow::update);
    connect(start, SIGNAL(triggered()), this, SLOT(startTimer()));
    connect(pause, SIGNAL(triggered()), this, SLOT(pauseTimer()));
    connect(help, SIGNAL(triggered()), this, SLOT(showHelp()));
}

void MainWindow::startTimer()
{
    if (!isTimerStart())
    {
        timer->start(TimeInterval * 1000);
        std::cout<<"Timer Start\n";
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
}

void MainWindow::update()
{
    std::cout<<"Time Out\n";
}

bool MainWindow::isTimerStart()
{
    return timerStatus;
}
