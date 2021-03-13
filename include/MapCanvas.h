/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-13
 * @file        : MapCanvas.h
 * @description : 用于绘制地图的画布，访问父窗口mainwindow的users列表查询坐标
*/

#ifndef __MAPCANVAS_H__
#define __MAPCANVAS_H__

#include <QtWidgets/QWidget>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <vector>
#include "User.h"

class MapCanvas : public QWidget
{
public:
    MapCanvas(QWidget *parent, std::vector<User *> &userList);

private:
    std::vector<User *> &list;
    QImage mapImg;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif
