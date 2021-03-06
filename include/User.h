/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-06
 * @file        : User.h
 * @description : 以栈的形式存储路径，根据计时器计算当前位置，
 *                对MainWindow暴露坐标用于渲染。根据坐标在
 *                地点列表中寻找附近地点。
*/

#pragma once
#ifndef __USER_H__
#define __USER_H__

#include <QtWidgets/QMainWindow>
#include <vector>
#include <utility>

class User
{

    Q_OBJECT;

public:
    int getX();
    int getY();
    void move();
    std::vector<std::pair<int, int>> getSpot();

    User();
};

#endif
