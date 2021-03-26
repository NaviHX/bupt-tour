/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-26
 * @file        : settingWnd.cpp
 * @description : 
*/

#include "settingWnd.h"
#include "global.h"
#include "Tour.h"
#include <cstdlib>

settingWnd::settingWnd()
{
    QLabel *label = new QLabel(tr("Time Interval :"), this);

    spinbox = new QSpinBox(this);
    spinbox->setRange(1, 100);
    spinbox->setValue(TimeInterval);

    timeButton=new QPushButton(tr("Change Time Interval"),this);

    changeButton = new QPushButton(tr("Change Load"), this);

    cons = new QTextEdit(this);
    cons->setReadOnly(true);

    layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(spinbox);
    layout->addWidget(timeButton);
    layout->addWidget(changeButton);
    layout->addWidget(cons);

    this->setWindowTitle(tr("Setting"));
    this->setLayout(layout);

    connect(timeButton, SIGNAL(pressed()), this, SLOT(setTimeInterval()));
    connect(changeButton, SIGNAL(pressed()), this, SLOT(changeLoad()));
}

settingWnd::~settingWnd()
{
}

void settingWnd::setTimeInterval()
{
    TimeInterval = spinbox->value();
}

void settingWnd::changeLoad()
{
    auto l_it = Load.begin();
    while (l_it != Load.end())
    {
        auto &v = l_it->second;
        for (auto it = v.begin(); it != v.end(); it++)
        {
            it->second = rand() % 101;
        }
        l_it++;
    }
    this->printLoad();
}

void settingWnd::printLoad()
{
    cons->clear();
    auto l_it = Load.begin();
    while (l_it != Load.end())
    {
        cons->insertPlainText(QString(l_it->first.c_str()) + ":\n");
        auto &v = l_it->second;
        for (auto it = v.begin(); it != v.end(); it++)
        {
            QString name(Building[it->first].c_str());
            int c = it->second;
            cons->insertPlainText(name + " : " + QString::number(c) + "\n");
        }
        l_it++;
    }
}
