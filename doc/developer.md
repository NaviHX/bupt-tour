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
|Congestion|n*n矩阵,拥挤程度(1-10)|`std::vector<vector<int>>`|
|DistanceBike|n*n矩阵，使用自行车道路时地点间的距离(不可达设置为-1)|`std::vector<vector<long long>>`|
|Direction|n*n矩阵，导航方向(使用int枚举)|`std::vector<vector<int>>`|
|Hint|n*n矩阵，导航提示语（暂不支持）|`std::vector<vector<std::string>>`|
|Speed|步行距离/单位时间|`int`|
|RideSpeed|骑行距离/单位时间|`int`|
|TimeInterval|刷新时间间隔，即单位时间(单位为秒)|`int`|
|BuildingCnt|总地点数|`int`|
|CnameCnt|别名个数|`int`|
|LoadBla|负载均衡配置个数|`int`|
|BusCount|公共交通配置个数|`int`|
|CurTime|当前时间|`int`|

所有全局变量从配置文件`config`中读入(除CurTime)

### 配置文件格式

```
n m l// 三个整数，表示地点数，道路数，骑行道路数
v1 v2// 步行速度 骑行速度
t // 初始刷新间隔
l // 负载均衡配置数
l // 逻辑地址数
b // 公共交通数
NNN1 XXX YYY VVV 
...
NNNn XXX YYY VVV // n行，地点名 x坐标 y坐标 是否可见
a b d c v
...
a b d c v // 步行道路 出发点 终点 距离(单位10米) 初始拥挤度 是否绘制
a b d c v
...
a b d c v // 骑行道路 出发点 终点 距离(单位10米) 初始拥挤度 是否绘制
// 负载均衡配置示例
名称 供均衡的地点个数 [地点 初始负载]
// 逻辑地址示例
原名 别名
// 公共交通  
// EOF
```

## 模块

|Name|Description|
|-|-|
|MainWindow|主窗口，承担UI绘制，处理用户输入的功能，继承自Qt主窗口,内部含有Qt计时器类|
|Tour|根据用户输入的信息处理最短路径|
|User|导航用户，保存路线信息，模拟进度|
|MapCanvas|地图画布组件|
|settingWnd|设置窗口组件|
|Bus|公共交通类，派生出定时发车公共交通与固定时间间隔发车公共交通|
|global|全局变量声明头文件|

## 类说明

### User

以栈的形式存储路径，根据计时器计算当前位置，对MainWindow暴露坐标用于渲染  
根据坐标在地点列表中寻找附近地点

方法
|Name|Type|Description|
|-|-|-|
|getX|`int`|获取X坐标|
|getY|`int`|获取Y坐标|
|move|`SLOT void`|移动UI位置(根据下一个目标点以及剩余的步数),走完返回0，途中返回1，到达一个路径点返回2+路径点id / / 引入公共交通后,会产生负数返回值,-1表示等待，-2及更小表示上车(车序号为返回值绝对值-2)|
|getSpot|`std::vector<std::pair<int, int>>`|获取用户附近地点和距离|
|getDes|int|获取目的地|
|getInterv|int|获取到达目的的间隔数|
|getStart|int|获取起始地点|
|getTurns|int|获取已经过去的间隔|

成员
|Name|Type|Description|
|-|-|-|
|turns|int|过去的间隔个数|
|wait|int|等车时长|

### Tour

使用最短路算法计算最短路径，所有最短路径存储在`std::stack<pair<int, int>>`，pair的第一个变量为下一地点的编号，第二个变量为所需的时间间隔（计时器超时次数）  
使用SPFA计算最短路径，分别求取各地点最短路及其路径前驱  
然后从目的地开始，不断找前驱，然后将路径信息入栈（相应的，使用最短路径时逐一出栈即可）

方法
|Name|Type|Description|
|-|-|-|
|getShortPath|`std::stack<pair<int, int>>`|直接计算最短路径|
|getCongestionPath|`std::stack<pair<int, int>>`|考虑拥挤度后的最短路径，边权为拥挤度*长度，默认拥挤度为5|
|getBikePath|`std::stack<pair<int, int>>`|与直接计算相比，使用专用的自行车地图|
|getSerialPath|`std::stack<pair<int, int>>`|不同段使用不同的导航策略|
|getId|int|依次根据负载均衡，别名，直接搜索的结果返回目的地编号|

成员
|Name|Type|Description|
|-|-|-|
|-|-|-|

### MainWindow

当用户选择好地图数据后，在窗口中绘制地图  
提供模拟计时器的开关  
提供用户的控制按钮  
提供日志输出窗口  

方法
|Name|Type|Description|
|-|-|-|
|startTimer|`SIGNAL`|启动计时器信号|
|pauseTimer|`SIGNAL`|暂停计时器信号|
|resetTimer|`SIGNAL`|重置计时器信号|
|render|`SLOT void`|在渲染用户所在地点|
|addUser|`SLOT void`|添加用户|
|moveUser|`SLOT void`|移动用户位置|
|deleteUser|`SLOT void`|删除用户|

## 项目规范

序言格式，新建源代码文件使用
```
/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : {NAME} 
 * @date        : {YEAR}-{MONTH}-{DATE}
 * @file        : {Filename}
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
