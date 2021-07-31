#pragma once

#include <QtWidgets/QWidget>
#include "ui_MyGraphicsView.h"

class MyGraphicsView : public QWidget
{
    Q_OBJECT

public:
    MyGraphicsView(QWidget *parent = Q_NULLPTR);

private:
    Ui::MyGraphicsViewClass ui;
};
