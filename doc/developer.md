# 设计文档

## 项目概述

实现校园内导航软件，根据时间轴推进导航的模拟进程。  
支持多个校区。  
同学在程序中输入起始地与目的地，软件给出相应的导航路径，确认后在地图上进行模拟导航。 
支持使用逻辑位置（即形如XX班YY课教室的地点）。  
支持多种导航策略，包括途径指定地点的最短路径，基于拥挤度的时间最短路径，乘坐某种交通工具的最短路径。  
实时查询位置，推荐附近地点及其路线，距离。  
实时更改导航目的地。  
多个用户同时导航。  
对食堂进行负载均衡导航。  
记录软件工作日志。  

UI采用`Qt 6.0.0`绘制  

## 数据结构

|Name|Description|Data Structure|
|-|-|-|
|Building|n维向量，存储建筑名|`std::vector<std::string>`|
|Id|哈希表，从建筑名到编号的映射|`std::map<std::string, int>`|
|Loc|n*2维向量，存储地点的坐标|`std::vetcor<std::vector<int>>`|
|Distance|n*n矩阵，地点间的距离(不可达设置为-1)|`std::vector<vector<long long>>`|
|Congestion|n*n矩阵,拥挤程度(1-100)|`std::vector<vector<int>>`|
|DistanceBike|n*n矩阵，使用自行车道路时地点间的距离(不可达设置为-1)|`std::vector<vector<long long>>`|
|Direction|n*n矩阵，导航方向(使用int枚举)|`std::vector<vector<int>>`|
|Hint|n*n矩阵，导航提示语|`std::vector<vector<std::string>>`|
|Speed|步行距离/单位时间|`int`|
|TimeInterval|刷新时间间隔，即单位时间(单位为秒)|`int`|

## 模块

|Name|Description|
|-|-|
|MainWindow|主窗口，承担UI绘制，处理用户输入的功能，继承自Qt主窗口|
|Timer|模拟计时器，每隔一段时间触发模拟进度推进和UI刷新|
|Tour|根据用户输入的信息处理最短路径|
|User|导航用户，保存路线信息，模拟进度|

## 成员与方法说明

## 项目规范

序言格式，新建源代码文件使用
```
/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author : {NAME} 
 * @date : {YEAR}-{MONTH}-{DATE}
 * @file : {Filename}
 * @description : 
*/
```

序言修改声明，修改源代码使用
```
/*
 * @modified by : {NAME}
 * @date        : {YEAR}-{MONTH}-{DATE}
 * @description : 
*/
```

类声明，写于类前
```
/*
 * @class       : 
 * @description : 
*/
```

函数声明，写于函数前
```
/*
 * @function    : 
 * @description : 
*/
```
