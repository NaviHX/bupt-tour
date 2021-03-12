/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-06
 * @file        : Tour.h
 * @description : 使用最短路算法计算最短路径
*/

#ifndef __TOUR_H__
#define __TOUR_H__

#include <stack>
#include <utility>
#include <vector>

class Tour
{

public:
    std::stack<std::pair<int, int>> getShortPath(int s, int e);
    std::stack<std::pair<int, int>> getCongestionPath(int s, int e);
    std::stack<std::pair<int, int>> getBikePath(int s, int e);
    std::stack<std::pair<int, int>> getSerialPath(std::vector<int> plots, std::vector<int> tactics);

    Tour();
    ~Tour();
};

#endif
