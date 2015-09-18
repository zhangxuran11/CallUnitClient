#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"callctlunit.h"
#include"config.h"
#include"stdio.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug()<<"1111111111111111111 \n";
    ui->setupUi(this);
    callUnit = new CallCtlUnit(ROOM_NO);
    callUnit2 = new CallCtlUnit(ROOM_NO*2);
    qDebug()<<"222222222222222222222 \n";
    connect(ui->pushButton,SIGNAL(clicked()),callUnit,SLOT(sendRoomCall()));
    connect(ui->pushButton_2,SIGNAL(clicked()),callUnit2,SLOT(sendRoomCall()));
    qDebug()<<"3333333333333333333 \n";
}

MainWindow::~MainWindow()
{
    delete callUnit;
    delete callUnit2;
    delete ui;
}
