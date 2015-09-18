#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QUdpSocket>
#include "parser.h"

/***********************************************************
  网络通讯类  负责与系统控制器服务器  视频主服务器 车厢控制器服务器通讯
  ***********************************************************/
class NetWork : public QObject
{
    Q_OBJECT
public:
    //succese return a valid pointer otherwise return NULL
    static GlobalControlPackageParser* queryTrainInfo();   //向系统控制器服务器查询信息
    static CarControlPackageParser*          queryCarInfo();     //向车厢控制器服务器查询信息
    //发送数据包 传入用于通信的udpsocket(必须是已邦定的)、要发送的包、和远程主机ip port
    static bool sendPkg(QUdpSocket& udpClient, ComPackageParser& parser,QHostAddress remote,quint16 port);
private:
    explicit NetWork(QObject *parent = 0);
};


#endif // NETWORK_H
