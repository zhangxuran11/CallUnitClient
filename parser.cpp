#include <QStringList>
#include "parser.h"

Parser::Parser(QObject *parent) :
    QObject(parent)
{
    msgHead = 0xaa55;
    checkSum = 0;
    msgEnd = 0x55aa;
}

quint8 Parser::genarateCheckSum()       //从包头累加到后三字节之前(不包括后三个字节)
{
    quint8 val = 0;
    for(int i = 0;i < dataFrame.length()-3;i++)
        val += static_cast<quint8>(dataFrame[i]);
    return val;
}

void ComPackageParser::init()
{
    cmd = 0;
//    extraData1.resize(10);
//    extraData2.resize(20);
//    extraData3.resize(40);
//    extraData4.resize(40);
    dataFrame.resize(FRAME_SIZE);
}
const quint16 ComPackageParser::FRAME_SIZE = 117;
ComPackageParser::ComPackageParser(QObject *parent):
    Parser(parent)
{
    init();
}
ComPackageParser::ComPackageParser(QByteArray bytes,QObject *parent):
    Parser(parent)
{
    init();
    memcpy(dataFrame.data(),bytes.data(),bytes.length());
    memcpy(&msgHead,dataFrame.data(),2);
    memcpy(&cmd,dataFrame.data()+2,2);
    extraData1 = QString::fromUtf8(dataFrame.data()+4,10).split(QChar('\0'))[0];
    extraData2 = QString::fromUtf8(dataFrame.data()+14,20).split(QChar('\0'))[0];
    extraData3 = QString::fromUtf8(dataFrame.data()+34,40).split(QChar('\0'))[0];
    extraData4 = QString::fromUtf8(dataFrame.data()+74,40).split(QChar('\0'))[0];
    memcpy(&checkSum,dataFrame.data()+114,1);
    memcpy(&msgEnd,dataFrame.data()+115,2);

}
/*************************************************
//  quint16     msgHead;                //2    0--1
    quint16     cmd;                    //2    2--3
    QByteArray  extraData1;             //10   4--13
    QByteArray  extraData2;             //20   14--33
    QByteArray  extraData3;             //40   34--73
    QByteArray  extraData4;             //40    74--113
//  quint8      checkSum;               //1    114
//  quint16     msgEnd;                 //2    115--116
*************************************************/


void ComPackageParser::genarate()
{
    dataFrame.resize(FRAME_SIZE);
    memcpy(dataFrame.data(),&msgHead,2);
    memcpy(dataFrame.data()+2,&cmd,2);
    memcpy(dataFrame.data()+4,extraData1.toUtf8().data(),10);
    memcpy(dataFrame.data()+14,extraData2.toUtf8().data(),20);
    memcpy(dataFrame.data()+34,extraData3.toUtf8().data(),40);
    memcpy(dataFrame.data()+74,extraData4.toUtf8().data(),40);
    checkSum = genarateCheckSum();
    memcpy(dataFrame.data()+114,&checkSum,1);
    memcpy(dataFrame.data()+115,&msgEnd,2);

}
/***************************************
//  quint16     msgHead;        //2     0--1
    QString     trainID;        //10    2--11
    QString     distStationTime;//10    12--21
    QString  nextStationTime;//10    22--31
    QString  startSTaion;    //10    32--41
    QString  distStaion;     //10    42--51
    QString     preStaion;      //10    52--61
    QString     nextStation;    //10    62--71
    QString     currentStaion;  //10    72--81
    qreal       outTemprature;  //5     82--86

    QByteArray  reserved;       //60    87--146
//  quint8      checkSum;       //1     147
//  quint16     msgEnd;         //2     148--149
****************************************/

void GlobalControlPackageParser::init()
{
    reserved.resize(60);
}
const quint16 GlobalControlPackageParser::FRAME_SIZE = 150;
GlobalControlPackageParser::GlobalControlPackageParser(QObject *parent):
    Parser(parent)
{
    init();
}
GlobalControlPackageParser::GlobalControlPackageParser(QByteArray bytes,QObject *parent):
    Parser(parent)
{
    init();
    dataFrame.clear();
    dataFrame.resize(FRAME_SIZE);
    memcpy(dataFrame.data(),bytes.data(),bytes.length());

    memcpy(&msgHead,dataFrame.data(),2);
    trainID = QString::fromUtf8(dataFrame.data()+2,10).split(QChar('\0'))[0];
    distStationTime = QString::fromUtf8(dataFrame.data()+12,10).split(QChar('\0'))[0];
    nextStationTime = QString::fromUtf8(dataFrame.data()+22,10).split(QChar('\0'))[0];
    startSTaion = QString::fromUtf8(dataFrame.data()+32,10).split(QChar('\0'))[0];
    distStaion = QString::fromUtf8(dataFrame.data()+42,10).split(QChar('\0'))[0];
    preStaion = QString::fromUtf8(dataFrame.data()+52,10).split(QChar('\0'))[0];
    nextStation = QString::fromUtf8(dataFrame.data()+62,10).split(QChar('\0'))[0];
    currentStaion = QString::fromUtf8(dataFrame.data()+72,10).split(QChar('\0'))[0];
    outTemprature = QString::fromUtf8(dataFrame.data()+82,5).toFloat();

    memcpy(reserved.data(),dataFrame.data()+87,60);
    checkSum = (quint8)dataFrame[147];
    memcpy(&msgEnd,dataFrame.data()+148,2);
}

void GlobalControlPackageParser::genarate()
{
    dataFrame.resize(FRAME_SIZE);
    memcpy(dataFrame.data(),&msgHead,2);
    memcpy(dataFrame.data()+2,trainID.toUtf8(),10);
    memcpy(dataFrame.data()+12,distStationTime.toUtf8().data(),10);
    memcpy(dataFrame.data()+22,nextStationTime.toUtf8().data(),10);
    memcpy(dataFrame.data()+32,startSTaion.toUtf8().data(),10);
    memcpy(dataFrame.data()+42,distStaion.toUtf8().data(),10);
    memcpy(dataFrame.data()+52,preStaion.toUtf8().data(),10);
    memcpy(dataFrame.data()+62,nextStation.toUtf8().data(),10);
    memcpy(dataFrame.data()+72,currentStaion.toUtf8().data(),10);
    memcpy(dataFrame.data()+82,QString::number(outTemprature,'f',2).toUtf8(),5);
    memcpy(dataFrame.data()+87,reserved.data(),60);
    checkSum = genarateCheckSum();
    memcpy(dataFrame.data()+147,&checkSum,1);
    memcpy(dataFrame.data()+148,&msgEnd,2);

}

/*********************************************************
//  quint16     msgHead;        //2     //0--1
    QString     carID;          //10    //2--11
    QString     currentTime;    //12    //12--23
    char        wcState;        //1     //24
    QByteArray  reserved;       //52    //25--76
//  quint8      checkSum;       //1     //77
//  quint16     msgEnd;         //2     //78--79
  **********************************************************/

void CarControlPackageParser::init()
{
    reserved.resize(52);
}
const quint16 CarControlPackageParser::FRAME_SIZE = 80;
CarControlPackageParser::CarControlPackageParser(QObject *parent):
        Parser(parent)
{
    init();
}
CarControlPackageParser::CarControlPackageParser(QByteArray bytes,QObject *parent):
    Parser(parent)
{
    init();
    dataFrame.resize(FRAME_SIZE);
    memcpy(dataFrame.data(),bytes.data(),bytes.length());

    memcpy(&msgHead,dataFrame.data(),2);
    carID = QString::fromUtf8(dataFrame.data()+2,10).split(QChar('\0'))[0];
    currentTime = QString::fromUtf8(dataFrame.data()+12,12).split(QChar('\0'))[0];
    wcState = dataFrame[24];
    memcpy(reserved.data(),dataFrame.data()+25,52);
    checkSum = (quint8)dataFrame[77];
    memcpy(&msgEnd,dataFrame.data()+78,2);

}
void CarControlPackageParser::genarate()
{
    dataFrame.resize(FRAME_SIZE);
    memcpy(dataFrame.data(),&msgHead,2);
    memcpy(dataFrame.data()+2,carID.toUtf8().data(),10);
    memcpy(dataFrame.data()+12,currentTime.toUtf8().data(),12);
    memcpy(dataFrame.data()+24,&wcState,1);
    memcpy(dataFrame.data()+25,reserved.data(),52);

    checkSum = genarateCheckSum();
    memcpy(dataFrame.data()+77,&checkSum,1);
    memcpy(dataFrame.data()+78,&msgEnd,2);
}


