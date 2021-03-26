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
#include <QtWidgets/QTextEdit>
#include <QtCore/QStringList>

#include <vector>

#include "Tour.h"
#include "User.h"
#include "MapCanvas.h"

class MainWindow : public QMainWindow
{

    Q_OBJECT;

public slots:
    void addUser();
    void startTimer();
    void pauseTimer();
    void showHelp();
    void findNearbyLoc();
    void changeDes();
    void showSetting();

public:
    MainWindow(QWidget *parent);

    std::vector<User *> myUsers;

private:
    void refresh();
    bool isTimerStart();
    void printOnCons(const QString &str);
    std::string* getPathStr(std::stack<std::pair<int, int>> &st);

    QAction *addOneUser;
    QAction *start;
    QAction *pause;
    QAction *help;

    QAction *findNearby;
    QAction *chDes;

    QStringList plotList;

    MapCanvas *canvas;
    QTextEdit *console;

    QTimer *timer;
    bool timerStatus;
    long long timerCount;

    QAction *setting;

    Tour *myTour;
};

#endif
