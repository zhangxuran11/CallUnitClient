#include "config.h"
#include"network.h"
#include "callctlunit.h"
#include "parser.h"
#include <QDebug>
CallCtlUnit::CallCtlUnit(int _roomNo,QObject *parent) :
    QObject(parent),roomNo(_roomNo)
{
    flag = false;
    callUnitCLient.bind(QHostAddress(QHostAddress::Any),0);
    connect(&callUnitCLient,SIGNAL(readyRead()),this,SLOT(readRoomCtlUnit()));
}
void CallCtlUnit::readRoomCtlUnit()
{
    char readBuff[ComPackageParser::FRAME_SIZE];
    qint64  readCount= 0,readLen = ComPackageParser::FRAME_SIZE;
    printf("readRoomCtlUnit   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    do
    {
        if((readCount = callUnitCLient.readDatagram(readBuff + ComPackageParser::FRAME_SIZE - readLen,readLen)) == -1)
            return ;
        readLen -= readCount;
    }while(readLen > 0);
    ComPackageParser parser(QByteArray(readBuff,ComPackageParser::FRAME_SIZE));
    qDebug()<<"recv from room ctl unit cmd:"<<parser.cmd;
    if(parser.cmd == 0x3001)
        flag = false;
}

void CallCtlUnit::sendRoomCall()
{

    ComPackageParser parser;
    parser.cmd = 0x3000;
    parser.extraData1  = QString::number(roomNo);
    if(!flag)
    {
        flag = true;
        parser.extraData2 = "on";
    }
    else
    {
        flag = false;
        parser.extraData2 = "off";
    }
    parser.genarate();
    if(NetWork::sendPkg(callUnitCLient,parser,QHostAddress(ROOM_CTL_UNIT_IP),ROOM_CTL_UNIT_PORT) == true)
        qDebug("send to room ctl unit succese!\n");
    else
        qDebug("send to room ctl unit falid!\n");

}
