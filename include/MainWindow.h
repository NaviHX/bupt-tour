/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-06
 * @file        : MainWindow.h
 * @description : 主窗口，承担UI绘制，处理用户
 *                输入的功能，继承自Qt主窗口
*/

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qaction.h>
#include <QtCore/QTimer>

#include <vector>

#include "Tour.h"
#include "User.h"

class MainWindow : public QMainWindow
{

    Q_OBJECT;

public slots:
    void addUser();
    void startTimer();
    void pauseTimer();
    void showHelp();

public:
    MainWindow(QWidget* parent);

private:
    void update();
    bool isTimerStart();

    QAction* addOneUser;
    QAction* start;
    QAction* pause;
    QAction* help;

    QTimer* timer;
    bool timerStatus;

    Tour* myTour;
    std::vector<User*> myUsers;
};

#endif
