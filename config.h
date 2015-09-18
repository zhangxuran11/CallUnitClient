#ifndef CONFIG_H
#define CONFIG_H
#define ROOM_NO     6
#define ROOM_CTL_UNIT_IP    "192.168.1.117"
#define ROOM_CTL_UNIT_PORT  8880
#define TRAIN_SERVER_IP "192.168.1.114" //系统控制器服务器
#define TRAIN_SERVER_PORT   8880
#define CAR_SERVER_IP   "192.168.1.114" //车厢控制器服务器
#define CAR_SERVER_PORT      8880
#define SERVER_IP "192.168.1.114"
#ifdef  __MAIN__
const char* SERVER_URL_ARR[]={
    "http://" SERVER_IP  ":8090/test1.sdp",
    "http://" SERVER_IP  ":8094/test2.sdp",
    "http://" SERVER_IP  ":8096/test3.sdp",
    "http://" SERVER_IP  ":8098/test4.sdp",
    "http://" SERVER_IP  ":8100/test5.sdp",
    "http://" SERVER_IP  ":8102/test6.sdp",
    "http://" SERVER_IP  ":8104/test7.sdp",
    "http://" SERVER_IP  ":8106/test8.sdp",
    "http://" SERVER_IP  ":8090/test1.sdp",
};
#else
extern const char* SERVER_URL_ARR[];
#endif
#endif // CONFIG_H
