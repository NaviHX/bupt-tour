/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-07
 * @file        : global.h
 * @description : 全局变量声明
*/

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <vector>
#include <map>
#include <string>

extern std::vector<std::string> Building;
extern std::map<std::string, int> Id;
extern std::vector<std::vector<int>> Loc;
extern std::vector<std::vector<long long>> Distance;
extern std::vector<std::vector<int>> Congestion;
extern std::vector<std::vector<long long>> DistanceBike;
extern std::vector<std::vector<int>> Direction;
extern std::vector<std::vector<std::string>> Hint;
extern int Speed;
extern int RideSpeed;
extern int TimeInterval;
extern int BuildingCnt;

#endif
