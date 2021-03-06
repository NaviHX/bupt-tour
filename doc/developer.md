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
|Building|n维向量，存储建筑名|`stl::vector<std::string>`|
|Id|哈希表，从建筑名到编号的映射|`stl::map<std::string, int>`|
|Distance|n*n矩阵，地点间的距离(不可达设置为-1)|`stl::vector<vector<long long>>`|
|Direction|n*n矩阵，导航方向(使用int枚举)|`stl::vector<vector<int>>`|
|Hint|n*n矩阵，导航提示语|`stl::vector<vector<std::string>>`|

## 模块

|Name|Description|
|-|-|
|MainWindow|主窗口，承担UI绘制，处理用户输入的功能，继承自Qt主窗口|
|Timer|模拟计时器，每隔一段时间触发模拟进度推进和UI刷新|
|Tour|根据用户输入的信息处理最短路径|
|User|导航用户，保存路线信息，模拟进度|


