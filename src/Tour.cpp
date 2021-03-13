/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-07
 * @file        : Tour.cpp
 * @description : 
*/

#include "Tour.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <cmath>

#define INFL 0x7fffffffffffffff
#define INF 0x7fffffff

std::vector<std::string> Building;
std::map<std::string, int> Id;
std::vector<std::vector<int>> Loc;
std::vector<std::vector<std::pair<int, long long>>> Distance;
std::vector<std::vector<bool>> Visual;
std::vector<std::vector<std::pair<int, int>>> Congestion;
std::vector<std::vector<std::pair<int, long long>>> DistanceBike;
std::vector<std::vector<bool>> VisualBike;
std::vector<std::vector<std::pair<int, int>>> Direction;
std::vector<std::vector<std::pair<int, std::string>>> Hint;
int Speed;
int RideSpeed;
int TimeInterval;
int BuildingCnt;

// 最短路算法所需
static int pre[1001];
static long long dis[1001];
static int turns[1001];

/*
 * @function    : Tour
 * @description : 构造函数,读入配置文件，初始化全局变量
*/
Tour::Tour()
{
    std::ifstream configFile;
    try
    {
        configFile.open("config", std::ios::in);
        int roadCnt, cycRoadCnt;

        // 初始化总数，速度，刷新时间
        configFile >> BuildingCnt >> roadCnt >> cycRoadCnt;
        configFile >> Speed >> RideSpeed;
        configFile >> TimeInterval;

        // 初始化地点信息 前三项
        for (int i = 0; i < BuildingCnt; i++)
        {
            std::string temp;
            int x, y, level;
            configFile >> temp >> x >> y >> level;
            std::vector<int> v(2);
            v[0] = x, v[1] = y;
            // 显示级别暂不使用，丢弃level值
            Building.push_back(temp);
            Loc.push_back(v);
            Id.insert(std::pair<std::string, int>(temp, i));
        }

        // 初始化路径信息
        Distance.resize(BuildingCnt);
        DistanceBike.resize(BuildingCnt);
        Visual.resize(BuildingCnt);
        VisualBike.resize(BuildingCnt);
        Congestion.resize(BuildingCnt);
        for (int i = 0; i < roadCnt; i++)
        {
            int from, to, weight, con, vis;
            configFile >> from >> to >> weight >> con >> vis;
            Distance[from].push_back(std::pair<int, long long>(to, weight));
            Visual[from].push_back(vis);
            Congestion[from].push_back(std::pair<int, int>(to, con));
            Distance[to].push_back(std::pair<int, long long>(from,weight));
            Visual[to].push_back(vis);
            Congestion[to].push_back(std::pair<int, int>(from, con));
        }
        for (int i = 0; i < cycRoadCnt; i++)
        {
            // 丢弃con
            int from, to, weight, con, vis;
            configFile >> from >> to >> weight >> con >> vis;
            DistanceBike[from].push_back(std::pair<int, long long>(to, static_cast<long long>(weight)));
            VisualBike[from].push_back(vis);
            DistanceBike[to].push_back(std::pair<int, long long>(from, static_cast<long long>(weight)));
            VisualBike[to].push_back(vis);
        }
    }
    catch (...)
    {
        std::cerr << "Cannot find config\n";
        exit(0);
    }
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
 * @description : 直接计算最短路，将从终点到起点的路径依次压入栈中，
 *                计算走两个相邻地点间所需的时间间隔。注意，应该将
 *                起点一起压入栈中，其所需的计时间隔设定为0。
 *                pair值定义详见开发文档
 * 
*/
std::stack<std::pair<int, int>> Tour::getShortPath(int s, int e)
{
    std::stack<std::pair<int, int>> res;
    std::queue<int> q;
    for (int i = 0; i < BuildingCnt; i++)
    {
        pre[i] = INF;
    }
    for (int i = 0; i < BuildingCnt; i++)
    {
        dis[i] = INFL;
    }
    dis[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int temp = q.front();
        for (int i = 0; i < Distance[temp].size(); i++)
        {
            int to = Distance[temp][i].first;
            long long weight = Distance[temp][i].second;
            if (dis[to] > dis[temp] + weight)
            {
                q.push(to);
                dis[to] = dis[temp] + weight;
                pre[to] = temp;
                turns[to] = ceil((double)weight / Speed);
                if (Visual[temp][i] == false)
                {
                    // 取反，作为不显示路径的标记
                    pre[to] = -temp;
                } // if end
            }     // if end
        }         // for end
        q.pop();
    } // while end
    if (pre[e] == INF)
    {
        return res;
    }
    int cur = e;
    while (cur != s)
    {
        res.push(std::pair<int, int>((pre[cur] < 0 ? -cur : cur), turns[cur]));
        cur = abs(pre[cur]);
    }
    res.push(std::pair<int, int>(s, 0));
    return res;
}

/*
 * @function    : getCongestionPath
 * @description : 计算考虑拥挤度的最短路
*/
std::stack<std::pair<int, int>> Tour::getCongestionPath(int s, int e)
{
    std::stack<std::pair<int, int>> res;
    std::queue<int> q;
    for (int i = 0; i < BuildingCnt; i++)
    {
        pre[i] = INF;
    }
    for (int i = 0; i < BuildingCnt; i++)
    {
        dis[i] = INF;
    }
    dis[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int temp = q.front();
        for (int i = 0; i < Distance[temp].size(); i++)
        {
            int to = Distance[temp][i].first;
            long long weight = Distance[temp][i].second * Congestion[temp][i].second / 5;
            if (dis[to] > dis[temp] + weight)
            {
                q.push(to);
                dis[to] = dis[temp] + weight;
                pre[to] = temp;
                turns[to] = ceil((double)weight / Speed);
                if (Visual[temp][i] == false)
                {
                    // 取反，作为不显示路径的标记
                    pre[to] = -temp;
                } // if end
            }     // if end
        }         // for end
        q.pop();
    } // while end
    if (pre[e] == INF)
    {
        return res;
    }
    int cur = e;
    while (cur != s)
    {
        res.push(std::pair<int, int>((pre[cur] < 0 ? -cur : cur), turns[cur]));
        cur = abs(pre[cur]);
    }
    res.push(std::pair<int, int>(s, 0));
    return res;
}

/*
 * @function    : getBiketPath
 * @description : 计算自行车地图的最短路
*/
std::stack<std::pair<int, int>> getBikePath(int s, int e)
{
    std::stack<std::pair<int, int>> res;
    std::queue<int> q;
    for (int i = 0; i < BuildingCnt; i++)
    {
        pre[i] = INF;
    }
    for (int i = 0; i < BuildingCnt; i++)
    {
        dis[i] = INF;
    }
    dis[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int temp = q.front();
        for (int i = 0; i < DistanceBike[temp].size(); i++)
        {
            int to = Distance[temp][i].first;
            long long weight = DistanceBike[temp][i].second;
            if (dis[to] > dis[temp] + weight)
            {
                q.push(to);
                dis[to] = dis[temp] + weight;
                pre[to] = temp;
                turns[to] = ceil((double)weight / Speed);
                if (Visual[temp][i] == false)
                {
                    // 取反，作为不显示路径的标记
                    pre[to] = -temp;
                } // if end
            }     // if end
        }         // for end
        q.pop();
    } // while end
    if (pre[e] == INF)
    {
        return res;
    }
    int cur = e;
    while (cur != s)
    {
        res.push(std::pair<int, int>((pre[cur] < 0 ? -cur : cur), turns[cur]));
        cur = abs(pre[cur]);
    }
    res.push(std::pair<int, int>(s, 0));
    return res;
}

/*
 * @function    : getSerialPath
 * @description : plots为路径点的编号列表，tactics为每一段路的导航策略列表，从后向前将最短路信息压入栈中
*/
std::stack<std::pair<int, int>> Tour::getSerialPath(std::vector<int> plots, std::vector<int> tactics)
{
    if(plots.size()<=1)
    {
        std::stack<std::pair<int, int>> emptyStack;
        return emptyStack;
    }
    std::stack<std::pair<int, int>> res, mid, mid2;
    for (int i = tactics.size() - 1; i >= 0; i--)
    {
        int t = tactics[i];
        int s = plots[i], e = plots[i + 1];
        switch (t)
        {
        case 0:
            mid = getShortPath(s, e);
            break;
        case 1:
            mid = getCongestionPath(s, e);
            break;
        case 2:
            mid = getShortPath(s, e);
            break;
        default:
            break;
        }
        if (mid.empty())
        {
            std::stack<std::pair<int, int>> emptyStack;
            return emptyStack;
        }
        while (!mid.empty())
        {
            std::pair<int, int> p = mid.top();
            mid2.push(p);
            mid.pop();
        }
        while (!mid2.empty())
        {
            std::pair<int, int> p = mid2.top();
            res.push(p);
            mid2.pop();
        }
    }
    return res;
}