#ifndef CALLCTLUNIT_H
#define CALLCTLUNIT_H

#include <QObject>
#include <QUdpSocket>
class CallCtlUnit : public QObject
{
    Q_OBJECT
    bool flag;//标志用户处于呼叫状态或者非呼叫状态
    const int roomNo;
    QUdpSocket callUnitCLient;
public:
    explicit CallCtlUnit(int _roomNo,QObject *parent = 0);
    
signals:
    
public slots:
    void sendRoomCall();
    void readRoomCtlUnit();
    
};

#endif // CALLCTLUNIT_H
