#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyGraphicsView.h"

class MyGraphicsView : public QMainWindow
{
    Q_OBJECT

public:
    MyGraphicsView(QWidget *parent = Q_NULLPTR);

private:
    Ui::MyGraphicsViewClass ui;
};
