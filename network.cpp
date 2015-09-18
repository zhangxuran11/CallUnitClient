#include "network.h"
#include "config.h"
#include <QUdpSocket>
#include <iostream>
using namespace std;
/********************************
  网络通讯类  负责与系统控制器

quint16     msgHead;    //2
quint16     cmd;        //2
QByteArray  extraData1; //10
QByteArray  extraData2; //20
QByteArray  extraData3; //40
QByteArray  extraData4; //40
quint8      chechSum;   //1
quint16     msgEnd;     //2

  *******************************/
NetWork::NetWork(QObject *parent) :
    QObject(parent)
{

}
//QUdpSocket* NetWork::trainUdp = new QUdpSocket();
//QUdpSocket* NetWork::carUdp = new QUdpSocket();
//void NetWork::init()
//{
//    trainUdp->bind(QHostAddress(QHostAddress::Any),0);
//    carUdp->bind(QHostAddress(QHostAddress::Any),0);
//}

bool NetWork::sendPkg(QUdpSocket& udpClient,ComPackageParser& comPackage, QHostAddress remote, quint16 port)
{
    qint64 writeCount = 0,writeLen = comPackage.dataPackage().length();
    do
    {
        if((writeCount =  udpClient.writeDatagram(comPackage.dataPackage().data() + comPackage.dataPackage().length() - writeLen,writeLen,remote,port)) == -1)
            return false;
        writeLen -= writeCount;
    }while(writeLen > 0);
    if(writeLen < 0)
        return false;
    return true;
}
GlobalControlPackageParser* NetWork::queryTrainInfo()
{
    QUdpSocket trainUdp;
    trainUdp.bind(QHostAddress(QHostAddress::Any),0);
    ComPackageParser comPackage;
    comPackage.cmd = 0x1000;
    comPackage.genarate();
    if(sendPkg(trainUdp,comPackage,QHostAddress(TRAIN_SERVER_IP),TRAIN_SERVER_PORT) == false)
        return NULL;
//    qint64 writeCount = 0,writeLen = comPackage.dataPackage().length();
//    do
//    {
//        if((writeCount =  trainUdp->writeDatagram(comPackage.dataPackage().data() + comPackage.dataPackage().length() - writeLen,writeLen,QHostAddress(TRAIN_SERVER_IP),TRAIN_SERVER_PORT)) == -1)
//            return NULL;
//        writeLen -= writeCount;
//    }while(writeLen > 0);
//    if(writeLen < 0)
//        return NULL;
    if(!trainUdp.waitForReadyRead(500))
    {
        return NULL;
    }
    char readBuff[GlobalControlPackageParser::FRAME_SIZE];
    qint64  readCount= 0,readLen = GlobalControlPackageParser::FRAME_SIZE;

    do
    {
        if((readCount = trainUdp.readDatagram(readBuff + GlobalControlPackageParser::FRAME_SIZE - readLen,readLen)) == -1)
            return NULL;
        readLen -= readCount;
    }while(readLen > 0);

    if(readLen < 0)
        return NULL;
    return new GlobalControlPackageParser(QByteArray(readBuff,GlobalControlPackageParser::FRAME_SIZE));
}


CarControlPackageParser*          NetWork::queryCarInfo()
{
    QUdpSocket carUdp;
    carUdp.bind(QHostAddress(QHostAddress::Any),0);
    ComPackageParser comPackage;
    comPackage.cmd = 0x2000;
    comPackage.genarate();
    if(sendPkg(carUdp,comPackage,QHostAddress(TRAIN_SERVER_IP),TRAIN_SERVER_PORT) == false)
        return NULL;
//    qint64 writeCount = 0,writeLen = comPackage.dataPackage().length();
//    do
//    {
//        if((writeCount =  carUdp->writeDatagram(comPackage.dataPackage().data() + comPackage.dataPackage().length() - writeLen,writeLen,QHostAddress(CAR_SERVER_IP),CAR_SERVER_PORT)) == -1)
//            return NULL;
//        writeLen -= writeCount;
//    }while(writeLen > 0);
//    if(writeLen < 0)
//        return NULL;
    if(!carUdp.waitForReadyRead(5000))
    {
        return NULL;
    }
    char readBuff[CarControlPackageParser::FRAME_SIZE];
    qint64  readCount= 0,readLen = CarControlPackageParser::FRAME_SIZE;
    do
    {
        if((readCount = carUdp.readDatagram(readBuff + CarControlPackageParser::FRAME_SIZE - readLen,readLen)) == -1)
            return NULL;
        readLen -= readCount;
    }while(readLen > 0);
    if(readLen < 0)
        return NULL;
    return new CarControlPackageParser(QByteArray(readBuff,CarControlPackageParser::FRAME_SIZE));

}




