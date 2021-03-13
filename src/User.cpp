/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-07
 * @file        : User.cpp
 * @description : 
*/

#include "User.h"
#include "global.h"
#include <stack>
#include <utility>

/*
 * @function    : User
 * @description : 初始化，储存最短路径信息，初始化坐标为起点坐标，将起点从栈中弹出
*/
User::User(std::stack<std::pair<int, int>> &path)
{
    if (!path.empty())
    {
        myPath = path;
        coordX = Loc[path.top().first][0];
        coordY = Loc[path.top().first][1];
        myPath.pop();
    }
}

/*
 * @function    : ~User
 * @description : 析构函数
*/
User::~User()
{
}

/*
 * @function    : getX
 * @description : 得到X坐标
*/
int User::getX()
{
    return coordX;
}

/*
 * @function    : getY
 * @description : 得到Y坐标
*/
int User::getY()
{
    return coordY;
}

/*
 * @function    : move
 * @description : 根据最短路径信息更改坐标
 *                首先判断路径是否走完，走完返回0，否则返回1
 *                检查栈顶元素pair的第二个元素（假设为step）是否为1，不为0就从全局变量loc中获取目标坐标（目标为pair第一个元素）
 *                计算当前坐标和目标坐标的差，移动差值/step，更新用户坐标值，step-1
 *                如果为，表明还有一步就到达目标点，直接将坐标值更改为目标坐标，将栈顶元素出栈
 *                所有计算类型始终为整型
*/
int User::move()
{
    if (myPath.empty())
        return 0;

    auto &temp = myPath.top();
    if (temp.second > 1)
    {
        coordX += (Loc[abs(temp.first)][0] - coordX) / temp.second;
        coordY += (Loc[abs(temp.first)][1] - coordY) / temp.second;
        temp.second--;
    }
    else
    {
        coordX = Loc[abs(temp.first)][0];
        coordY = Loc[abs(temp.first)][1];
        myPath.pop();
    }
    return 1;
}

/*
 * @function    : getSpot
 * @description : 找到附近的地点。从当前的目的地开始(栈顶元素的第一个量)，寻找至多经过一个地点可达的所有地点
*/
std::vector<std::pair<int, int>> User::getSpot()
{
}

/*
 * @function    : getDes
 * @description : 
*/
int User::getDes()
{
    if(myPath.empty())
        return -1;
    return myPath.top().first;
}