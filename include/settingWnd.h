/*
 * Copyright © 2021 BUPT-Tour. All rights reserved.
 * @author      : Navi.HuangXing 
 * @date        : 2021-03-26
 * @file        : settingWnd.h
 * @description : 
*/

#ifndef __SETTINGWND_H__
#define __SETTINGWND_H__

#include <QtWidgets/QWidget>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include "global.h"

class settingWnd : public QWidget
{

    Q_OBJECT;

public:
    settingWnd();
    ~settingWnd();

private:
    QSpinBox *spinbox;
    QLayout *layout;
    QPushButton *changeButton;
    QTextEdit *cons;
    QPushButton *timeButton;

private slots:
    void setTimeInterval();
    void changeLoad();
    void printLoad();
};

#endif
