#include <QtGui/QApplication>
#include "mainwindow.h"
#include<cstdio>
#include<QDebug>
int main(int argc, char *argv[])
{
    qDebug()<<"0000000000000000000 \n";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qDebug()<<"111111111111111 \n";
    return a.exec();
}
