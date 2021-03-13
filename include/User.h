/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-06
 * @file        : User.h
 * @description : 以栈的形式存储路径，根据计时器计算当前位置，
 *                对MainWindow暴露坐标用于渲染。根据坐标在
 *                地点列表中寻找附近地点。
*/

#ifndef __USER_H__
#define __USER_H__

#include <QtWidgets/QMainWindow>
#include <vector>
#include <utility>
#include <stack>

class User
{
public:
    int getX();
    int getY();
    int getDes();
    int move();
    std::vector<std::pair<int, int>> getSpot();

    User(std::stack<std::pair<int, int>>& path);
    ~User();

private:
    int coordX;
    int coordY;
    std::stack<std::pair<int, int>> myPath;
};

#endif
