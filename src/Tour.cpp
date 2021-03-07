/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-07
 * @file        : Tour.cpp
 * @description : 
*/

#include "Tour.h"
#include "global.h"

/*
 * @function    : Tour
 * @description : 构造函数,读入配置文件，初始化全局变量
*/
Tour::Tour()
{

}

/*
 * @function    : ~Tour
 * @description : 析构函数
*/
Tour::~Tour()
{

}

/*
 * @function    : getShortPath
 * @description : 直接计算最短路，将从终点到起点的路径依次压入栈中，计算走两个相邻地点间所需的时间间隔
*/
std::stack<std::pair<int, int>> Tour::getShortPath(int s, int e)
{

}

/*
 * @function    : getCongestionPath
 * @description : 计算考虑拥挤度的最短路
*/
std::stack<std::pair<int, int>> Tour::getCongestionPath(int s, int e)
{

}

/*
 * @function    : getBiketPath
 * @description : 计算自行车地图的最短路
*/
std::stack<std::pair<int, int>> getBiketPath(int s, int e)
{

}

/*
 * @function    : getSerialPath
 * @description : plots为路径点的编号列表，tactics为每一段路的导航策略列表，从后向前将最短路信息压入栈中
*/
std::stack<std::pair<int, int>> Tour::getSerialPath(std::vector<int> plots, std::vector<int> tactics)
{

}