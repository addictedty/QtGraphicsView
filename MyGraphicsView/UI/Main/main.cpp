#include "MyGraphicsView.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGraphicsView w;
    w.show();
    return a.exec();
}
