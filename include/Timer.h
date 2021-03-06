/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-06
 * @file        : Timer.h
 * @description : 控制用户位置的刷新频率
*/

#pragma once
#ifndef __TIMER_H__
#define __TIMER_H__

#include <QtWidgets/QMainWindow>

class Timer
{

    Q_OBJECT;

signals:
    void timeOut();

public slots:
    void start();
    void pause();
    void reset();

    Timer();
};

#endif
