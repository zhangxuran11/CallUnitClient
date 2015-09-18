#ifndef PARSER_H
#define PARSER_H

#include <QObject>

class Parser : public QObject
{
    Q_OBJECT
protected:
    quint16     msgHead;
    quint8      checkSum;
    quint16     msgEnd;
    QByteArray  dataFrame;


protected:
    quint8       genarateCheckSum();  //从包头累加到后三字节之前(不包括后三个字节)
public:
    explicit Parser(QObject *parent = 0);
    const char* getData(){return dataFrame.data();}
    bool        isValid(){return checkSum==genarateCheckSum();}

    virtual void genarate() = 0;
    
signals:
    
public slots:
    
};


class ComPackageParser:public Parser
{
    Q_OBJECT
public:
    static const quint16 FRAME_SIZE;
public:
//  quint16     msgHead;
    quint16     cmd;
    QString  extraData1;
    QString  extraData2;
    QString  extraData3;
    QString  extraData4;
//  quint8      checkSum;
//  quint16     msgEnd;
private:
    void init();
public:
    explicit ComPackageParser(QObject *parent = 0);
    explicit ComPackageParser(QByteArray bytes,QObject *parent = 0);
    const QByteArray &dataPackage(){return dataFrame;}
    void genarate();


};

class GlobalControlPackageParser:public Parser    //系统控制器数据包
{
    Q_OBJECT
public:
    static const quint16 FRAME_SIZE;
public:
//  quint16     msgHead;        //2
    QString     trainID;        //10
    QString     distStationTime;//10
    QString  nextStationTime;//10
    QString  startSTaion;    //10
    QString  distStaion;     //10
    QString     preStaion;      //10
    QString     nextStation;    //10
    QString     currentStaion;  //10
    qreal       outTemprature;  //5
    QByteArray  reserved;       //60
//  quint8      checkSum;       //1
//  quint16     msgEnd;         //2
private:
    void init();
public:
    explicit GlobalControlPackageParser(QObject *parent = 0);
    explicit GlobalControlPackageParser(QByteArray bytes,QObject *parent = 0);
    void genarate();


};

class CarControlPackageParser:public Parser //车厢控制器数据包
{
    Q_OBJECT
public:
    static const quint16 FRAME_SIZE;
public:
//  quint16     msgHead;        //2     //0--1
    QString     carID;          //10    //2--11
    QString     currentTime;    //12    //12--23
    char        wcState;        //1     //24
    QByteArray  reserved;       //52    //25--76
//  quint8      checkSum;       //1     //77
//  quint16     msgEnd;         //2     //78--79
private:
    void init();
public:
    explicit CarControlPackageParser(QObject *parent = 0);
    explicit CarControlPackageParser(QByteArray bytes,QObject *parent = 0);
    void genarate();

};

#endif // PARSER_H
