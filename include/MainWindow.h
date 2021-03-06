/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-06
 * @file        : MainWindow.h
 * @description : 主窗口，承担UI绘制，处理用户
 *                输入的功能，继承自Qt主窗口
*/

#pragma once
#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow
{

    Q_OBJECT;

signals:
    void startTimer();
    void pauseTimer();
    void resetTimer();

public slots:
    void addUser();
    void moveUser();
    void deleteUser();

public:
    MainWindow();
};

#endif
