/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-13
 * @file        : MapCanvas.cpp
 * @description : 
*/

#include "MapCanvas.h"

/*
 * @function    : MapCanvas
 * @description : 构造函数
*/
MapCanvas::MapCanvas(QWidget *parent, std::vector<User *> &userList) : QWidget(parent),
                                                                       list(userList)
{
    this->resize(QSize(960, 540));
    mapImg.load("./img/bupt-map.png");
}

/*
 * @function    : paintEvent
 * @description : 绘制地图事件
*/
void MapCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QColor colorList[3] = {Qt::red, Qt::blue, Qt::green};
    QPainter painter(this);
    painter.drawImage(QRect(0, 0, 960, 434), mapImg);
    for (int i = 0; i < list.size(); i++)
    {
        painter.setPen(colorList[i]);
        try
        {
            if (list[i] != nullptr && list[i]->getDes() >= 0)
            {
                int x = list[i]->getX();
                int y = list[i]->getY();
                // painter.drawLine(x - 5, y, x + 5, y);
                // painter.drawLine(x, y - 5, x, y + 5);
                painter.fillRect(x - 10, y - 3, 20, 6, colorList[i]);
                painter.fillRect(x - 3, y - 10, 6, 20, colorList[i]);
            }
        }
        catch (...)
        {
            continue;
        }
    }
}
