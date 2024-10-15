#pragma once
#include <fstream>

#include "ProtocalParser.h"
#include "FileUtils.h"
#include "DeviceNowPlayItem.h"
#include "DeviceType.h"
#include "DeviceNowPlayList.h"
#include <ctime>

#ifdef WIN32
#include "winsock.h"
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif

#include "SocketResult.h"
#include "NovaUtils.h"
#include <sstream>
#include <list>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/wait.h>


struct BrightnessItem
{
	int environment;//环境亮度
	int screen;//屏体亮度
};

struct DeviceNetBasicParam {
	char* deviceIp; //"192.168.0.220"
	int port;//500
    char* mark;//255.255.255.0
    char* gate;//192.168.0.1
    char* serviceIp;//当卡为客户端时候，这个就是服务端对应IP；当卡为服务端时，无效。
};

struct  DeviceSize
{
	int width;
	int height;
};

struct  DeviceMemorySize
{
	int totolSize;//单位MB
	int remainSize;//单位MB
	DeviceMemorySize(int totolSize, int remainSize) {
		this->totolSize = totolSize;
		this->remainSize = remainSize;
	}
};

struct TimeZoneParam {
	long long utcTime;//1565409600000
    char* timeZoneId;//Asia/Shanghai
    char* gmt;//GMT+08:00
	TimeZoneParam(long long utcTime, char* timeZoneId, char* gmt) {
		this->utcTime = utcTime;
		this->timeZoneId = timeZoneId;
		this->gmt = gmt;
	}
};

struct DeviceNTPParam {
	bool isOpen;
    char* addr; //utf-8 ntp服务器地址

	DeviceNTPParam(bool isOpen, char* addr) {
		this->isOpen = isOpen;
		this->addr = addr;
	}
};

struct DevicePowerByTimeParam {
	tm start;
	tm end;
	DevicePowerByTimeParam(tm start, tm end) {
		this->start = start;
		this->end = end;
	}
};
struct PlayByTimeParam {
	tm start;
	tm end;
	int id;
	PlayByTimeParam(tm start, tm end, int id) {
		this->start = start;
		this->end = end;
		this->id = id;
	}
};

struct BrightnessByTimeParam {
	tm start;
	tm end;
	int brightness;
	BrightnessByTimeParam(tm start,
		tm end,
		int brightness) {
		this->start = start;
		this->end = end;
		this->brightness = brightness;
	}

};
struct DeviceSecretParam {
    char* password; //viplex账号密码 默认123456
	bool isDesOpen;
	bool isMD5Open;
    char* desPassword; //des密码 必须是8位

	DeviceSecretParam(char* password, bool isDesOpen, bool isMD5Open, char* desPassword) {
		this->password = password;
		this->isDesOpen = isDesOpen;
		this->isMD5Open = isMD5Open;
		this->desPassword = desPassword;
	}
};

//屏幕监控信息
struct ScreenMonitorData {
	struct DevMapping {
		int devIndex;             //该种设备串联上的第几个
		int devType;              //设备类型
	};
	//接收卡的监控信息
	struct ScannerMonitorInfo {
		float temprature;          //接收卡本板温度
		float voltage;             //接收卡本板电压
		list<DevMapping> devMappingList;   //设备搜索映射
		int devWorkStatus;         //工作状态 0正常，1错误，2未知
	};
	struct PortOfSenderMonitorInfo {
		list<DevMapping> devMappingList;   //设备搜索映射
		int devWorkStatus;         //工作状态 0正常，1错误，2未知
	};
	//发送卡监控信息
	struct SenderMonitorInfo {
		bool isDVIConnected;         // DVI源是否连接
		int mDVIRate;                // DVI刷新率，仅在DVI连接时才有效
		int devWorkStatus;           //工作状态 0正常，1错误，2未知
		list<DevMapping> devMappingList;   //设备搜索映射
		list<PortOfSenderMonitorInfo> reduPortOfSenderList;   //进入冗余状态的网口的列表
	};
	//执行结果，0失败，1成功
	int code = 0;       
	//接收卡状态
	list<ScreenMonitorData::ScannerMonitorInfo> scannerMonitorInfoList;
	//发送卡监控
	list<ScreenMonitorData::SenderMonitorInfo> senderMonitorInfoList;
};
//视频源控制
struct VideoControlInfo {
	int code = 0;		  //响应码 0失败、1成功
	int videoSource;      //视频源 0 内部、1 HDMI
	//boolean isScale;      //是否启用全屏缩放（仅HDMI源生效）
	//int offsetX;		  //输出位置x坐标
	//int offsetY;		  //输出位置y坐标
};
//分辨率信息
struct EdidInfo{
	int code = 0;		 //响应码 0失败、1成功
	int width;           //宽
	int height;		     //高
	int fieldRate;		 //帧率
};
//分辨率信息
struct CustomDisplay {
	int code = 0;		 //响应码 0失败、1成功
	int width;           //宽
	int height;		     //高
};



struct CpuAndMemoryInfo {
    int code = 0;   //响应码 0失败、1成功
    int cpu;          //cpu使用率
    int totalMemory;  //总内存
    int freeMemory;   //剩余内存
};

struct CpuAndMemoryUseRateInfo {
    int code = 0;   //响应码 0失败、1成功
    int cpu;        //cpu使用率
    float memory;   //内存使用率
};

struct PointDetectResult{
    int code = 0;
    int badPointCount = 0;
};


class NovaTraffic {
private:
    //static const int SUCCESS = 1;
    static const int TEMP_SIZE = 100;
    static const int BIG_SIZE = 8192;
    static const int MAX_FAIL_COUNT = 3;
private:
    const char *ip = NULL;
    u_short port;
    int mSocket = -1;
    ProtocalParser *mProtocalParser = NULL;
    char *mDesStr = NULL;
    bool mIsServer = false;
    int connectTimeout = 10000;
    int sendTimeout = 10000;
    int recvTimeout = 10000;

private:
    char *recv(int socket, char what, int *recvSize);

    char *recv(int sockClient, char what, int *recvSize, int temp_size);

    int sendPlayFileName(int socket, int id);

    int sendFileName(int socket, const char *name, int len);

    int sendContent(int socket, char *content, int len, int id);

    int recvFileOverRsp(int socket);

    int sendPlayId(int socket, int id);

    int normalSet(char sendWhat, char recvWhat, char *bytes, int dataSize);

    int getSocket();

    void closeSocket(int novaSocket);

    int sendFileContent(int socket, const char *fileName, const int outSize, int *lastZize, int *itemNum);

    SocketResult *getData(char req, char rsp, char *buf, int dataSize);

    SocketResult *getData(int socket, char req, char rsp, char *buf, int dataSize);

    SocketResult *getBigData(char req, char rsp, char *buf, int dataSize);

    SocketResult *getData(char req, char rsp, char *buf, int dataSize, int bufferSize);

    SocketResult *getData(int socket, char req, char rsp, char *buf, int dataSize, int bufferSize);

    //获取点检数据
    SocketResult *getDetectErrorPointData(int socket, char req, char rsp, char rsp1, char *buf, int dataSize);

    SocketResult *getDetectErrorPointData(int socket, char req, char rsp, char rsp1, char *buf, int dataSize, int bufferSize);

    char *makeSendPacket(char what, char *data, int dataSize, int *outSize);


public:
    NovaTraffic(int mSocket);

    NovaTraffic(const char *ip, const u_short port);

    ~NovaTraffic();

    //数据加密的key
    void setDesKey(char *password);

    char *getDeviceName();

    int sendPlayList(int id, char *content);

    int playListById(int id);

    //局部更新
    int sendLocalUpdate(int id, char *content);

    int removeLocalUpdate(int id);

    int sendFile(const char *fileName, const char *saveFileName);

    int setBrightness(int brightness);

    int cleanUpFiles(int type);

    int setPower(bool power);

    DeviceNowPlayItem *getNowPlayContent();

    DeviceNowPlayList *getNowPlayAllContent();

    DeviceType *getDeviceType();

    int setTime(tm *date);

    int restartDevice();

    /**
     * 设置自动亮度调节
     * @param brightnessItem  必须是8组
     * @return
     */
    int setBrightnessAuto(BrightnessItem *brightnessItem);

    //获取自动亮度调节
    BrightnessItem *getBrightnessAuto();

    /*设置设备名称*/
    int setDeviceName(const char *name);

    //控制本板电源和屏幕黑屏
    int setBoardPowerAndScreenPower(bool power);

    //控制本板电源
    int setBoardPower(bool power);

    /**
    * 控制多功能卡电源
    * @param cardIndex 0-255 多功能卡位置索引
    * @param roadIndex  0-7     电源路数索引
    * @param power
    * @return
    */
    int setMultiFunctionCardPower(int cardIndex, int roadIndex, bool power);

    //恢复ip到出厂的192.168.0.220
    void resetDeviceIpToDefault();

    //获取控制卡版本
    char *getDeviceVersion();

    //设置屏体基本参数
    void setDeviceNetBasicParam(DeviceNetBasicParam mDeviceBasicParam);

    //获取屏幕尺寸（宽高）
    DeviceSize *getDeviceSize();

    //设置音量0 - 100
    int setDeviceVolume(int volume);

    //获取设备空间
    DeviceMemorySize *getDeviceMemorySize();

    // 设置时区
    int setTimeAndTimeZone(TimeZoneParam timeZoneParam);

    //获取时区
    TimeZoneParam *getTimeAndTimeZone();

    //设置ntp对时参数
    int setDeviceNTPParam(DeviceNTPParam deviceNTPParam);

    //获取ntp对时参数
    DeviceNTPParam *getDeviceNTPParam();

    //设置屏体关闭温度，高于此温度关屏
    // @param value 系统最小值为 70  0 表示不进行关屏处理
    int setCloseScreenTemperature(int value);

    //获取 屏体关闭温度
    int getCloseScreenTemperature();

    /*
     * 设置虚连接播放文件
     * @param isOpen false-不开启  true-开启虚连接检测
     * @param secondTime 单位秒，多长时间无数据交互开启虚连接
     * @param id 播放文件id 1 代表play001.lst文件
    */
    int setVirtualConnection(bool isOpen, int secondTime, int id);

    //发送ftp下载文件地址
    int sendFtpDownloadaddress(char *url);

    //升级文件
    int updateFileName(char *path);

    //移除app
    int removeAppPageName(char *pageName);

    /**
    * 获取当前播放截图
    * @param path 截图文件名
    * @return
    */
    int getDeviceScreenshot(const char *filePath);

    /**
    * 设置定时开屏列表
    * @param list  为null 或 0 清除操作 ；新表覆盖旧表
    * @return
    */
    int setDevicePowerByTimeList(std::list <DevicePowerByTimeParam> li);

    //获取定时开屏列表
    list <DevicePowerByTimeParam> *getDevicePowerByTimeList();

    // 设置定时播放列表
    int setPlayByTimeList(list <PlayByTimeParam> list);

    // 获取定时播放列表
    list <PlayByTimeParam> *getPlayByTimeList();

    //设置定时亮度列表
    int setBrightnessByTimeList(list <BrightnessByTimeParam> li);

    // 获取定时亮度列表
    list <BrightnessByTimeParam> *getBrightnessByTimeList();

    //设置设备加密
    int setDeviceSecretParam(DeviceSecretParam mDeviceSecretParam);

    CpuAndMemoryInfo getCpuAndMemoryInfo();

    CpuAndMemoryUseRateInfo getCpuAndMemoryUseRate();

    //获取检视信息
    ScreenMonitorData getSurveil();

    void sendHeartBeat();

    //获取视频控制模式
    VideoControlInfo getVideoControlInfo();

    //设置视频控制模式
    int setVideoControlInfo(int videoSource);

    //获取HDMI视频源分辨率
    EdidInfo getEdidInfo();

    //设置HDMI视频源分辨率
    int setEdidInfo(EdidInfo info);

    //设置内源分辨率
    int setCustomResolution(int width, int height);

    //获取内源分辨率
    CustomDisplay getCurrentResolution();

    list<int> getAllPlaylistId();


    char *readBadPointInfo();

    int getBrightValue();

    void setSocketTimeout(int connectTimeout, int sendTimeout, int recvTimeout);
};
