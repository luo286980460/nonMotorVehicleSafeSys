#pragma once

#include <iostream> 
#include <stdio.h>
#include <string.h>
#include <vector>
#include "DES.h"
using namespace std;

#define byte char
#define null NULL
#define boolean bool
#define _IP_MARK "."


static int PACKET_WITHOUT_DATA_SIZE = 7;
static int PACKET_START_OFFSET = 0;
static char PACKET_TRANSFER_FLAG = (char)0xEE;
static char PACKET_START_FLAG = (char)0xAA;
static char PACKET_END_FLAG = (char)0xCC;

static char PACKET_DEVICEID_ARG1 = (char)0xff;
static char PACKET_DEVICEID_ARG2 = (char)0xff;
static char DES_ADD_SIZE = 7;

static char WHAT_NO_RSP = -0x01;
static char WHAT_HEART_BEAT = 0x00;
static char WHAT_GET_DEVICE_TYPE_REQ = 0x01;
static char WHAT_GET_DEVICE_TYPE_RSP = 0x02;
static char WHAT_SCREEN_POWER_REQ = 0x05;
static char WHAT_SCREEN_POWER_RSP = 0x06;

static char WHAT_SCREEN_BRIGHTNESS_MODE_REQ = 0x07;
static char WHAT_SCREEN_BRIGHTNESS_MODE_RSP = 0x08;
static char WHAT_DEVICE_SET_TIME_REQ = 0x09;
static char WHAT_DEVICE_SET_TIME_RSP = 0x0a;
static char WHAT_SCREEN_POINT_DETECT_REQ = 0x0B;
static char WHAT_SCREEN_POINT_DETECT_RSP = 0x0C;
static char WHAT_DEVICE_REBOOT_REQ = 0x0d;
static char WHAT_DEVICE_REBOOT_RSP = 0x0e;
static char WHAT_FILENAME_REQ = 0x11;
static char WHAT_FILENAME_RSP = 0x12;
static char WHAT_FILESEND_REQ = 0x13;
static char WHAT_FILESEND_RSP = 0x14;

static char WHAT_SET_ENVIRONMENT_ALARM_REQ = 0x15;
static char WHAT_SET_ENVIRONMENT_ALARM_RSP = 0x16;

static char WHAT_SCREEN_BRIGHTNESS_SET_AUTO_MODE_PARAM_REQ = 0x17;
static char WHAT_SCREEN_BRIGHTNESS_SET_AUTO_MODE_PARAM_RSP = 0x18;

static char WHAT_SET_DEVICE_IP_REQ = 0x19;
static char WHAT_SET_DEVICE_IP_RSP = 0x1A;

static char WHAT_PLAYBYLIST_REQ = 0x1B;
static char WHAT_PLAYBYLIST_RSP = 0x1C;

static char WHAT_DEVICE_RESET_IP_REQ = 0x21;
static char WHAT_DEVICE_RESET_IP_RSP = 0x22;

static char WHAT_QUERY_VERSIONINFO_REQ = 0x23;
static char WHAT_QUERY_VERSIONINFO_RSP = 0x24;

static char WHAT_SCREEN_MY_BOARD_POWER_AND_POWER_REQ = 0x25;
static char WHAT_SCREEN_MY_BOARD_POWER_AND_POWER_RSP = 0x26;

static char WHAT_GET_ENVIRONMENT_ALARM_REQ = 0x29;
static char WHAT_GET_ENVIRONMENT_ALARM_RSP = 0x2A;

static char WHAT_SCREEN_BRIGHTNESS_GET_AUTO_MODE_PARAM_REQ = 0x2B;
static char WHAT_SCREEN_BRIGHTNESS_GET_AUTO_MODE_PARAM_RSP = 0x2C;

static char WHAT_GET_PLAYING_ITEM_REQ = 0x2D;
static char WHAT_GET_PLAYING_ITEM_RSP = 0x2E;
static char WHAT_GET_PLAYING_ALL_REQ = 0x3A;
static char WHAT_GET_PLAYING_ALL_RSP = 0x3B;

static char WHAT_GET_ERROR_POINT_REQ1 = 0x36;
static char WHAT_GET_ERROR_POINT_RSP1 = 0x37;
static char WHAT_GET_ERROR_POINT_RSP2 = 0x38;
static char WHAT_GET_ERROR_POINT_REQ2 = 0x39;

static char WHAT_SET_TIMING_PLAYLIST_PARAM_REQ = 0x41;
static char WHAT_SET_TIMING_PLAYLIST_PARAM_RSP = 0x42;

static char WHAT_SCREEN_BRIGHTNESS_SET_TIMING_MODE_PARAM_REQ = 0x43;
static char WHAT_SCREEN_BRIGHTNESS_SET_TIMING_MODE_PARAM_RSP = 0x44;

static char WHAT_SET_VOLUME_PARAM_REQ = 0x45;
static char WHAT_SET_VOLUME_PARAM_RSP = 0x46;

static char WHAT_GET_SDCARD_SIZE_REQ = 0x47;
static char WHAT_GET_SDCARD_SIZE_RSP = 0x48;

static char WHAT_SET_FTP_DOWNLOAD_REQ = 0x49;
static char WHAT_SET_FTP_DOWNLOAD_RSP = 0x50;

static char GET_SCREEN_BRIGHTNESS_SET_TIMING_MODE_PARAM_INFO = (char)0x51;
static char GET_SCREEN_OPEN_CLOSE_SET_TIMING_PARAM_INFO = (char)0x52;
static char GET_SCREEN_TIMING_PLAYLIST_PARAM_INFO = (char)0x53;

static char WHAT_SECRET_DES_MD5_REQ = 0x70;
static char WHAT_SECRET_DES_MD5_RSP = 0x71;

static char WHAT_DEVICE_NAME_REQ = 0x7E;
static char WHAT_DEVICE_NAME_RSP = 0x7F;

static char WHAT_CLEAN_PLAYLIST_REQ = 0x7C;
static char WHAT_CLEAN_PLAYLIST_RSP = 0x7D;

static char WHAT_SCREENSHOT_REQ = (char)0x80;
static char WHAT_SCREENSHOT_RSP = (char)0x81;

static char WHAT_SCREEN_WIDTH_HEIGHT_REQ = (char)0x82;
static char WHAT_SCREEN_WIDTH_HEIGHT_RSP = (char)0x83;

static char WHAT_SCREEN_MY_BOARD_POWER_REQ = (char)0x84;
static char WHAT_SCREEN_MY_BOARD_POWER_RSP = (char)0x85;

static char WHAT_FUNCTION_CARD_POWER_REQ = (char)0x86;
static char WHAT_FUNCTION_CARD_POWER_RSP = (char)0x87;

static char WHAT_REGION_UPDATE_REQ = (char)0x88;
static char WHAT_REGION_UPDATE_RSP = (char)0x89;

static char WHAT_SCREEN_OPEN_CLOSE_SET_TIMING_PARAM_REQ = (char)0x8A;
static char WHAT_SCREEN_OPEN_CLOSE_SET_TIMING_PARAM_RSP = (char)0x8B;

static char WHAT_SYSTEM_UPDATE_REQ = (char)0x90;
static char WHAT_SYSTEM_UPDATE_RSP = (char)0x91;

static char SET_TIME_AND_ZONE = (char)0x95;
static char GET_TIME_AND_ZONE = (char)0x96;
static char SET_NTP_PARAM = (char)0x97;
static char GET_NTP_PARAM = (char)0x98;

static char SET_RELAY = (char)0x9e;
static char WHAT_APP_REMOVE = (char)0x9f;

static char WHAT_VIRTUAL_CONNECT_PARAM_REQ = (char)0xF3;
static char WHAT_VIRTUAL_CONNECT_PARAM_RSP = (char)0xF4;

static char WHAT_FILESEND_OVER_RSP = (char)0xF9;

static char WHAT_GET_SURVEIL = (char)0xA0;

//获取视频源控制方式
static char  WHAT_GET_VIDEO_SOURCE_CONTROL_MODE = (char)0xA1;
//获取视频源分辨率
static char  WHAT_GET_VIDEO_SOURCE = (char)0xA2;
//设置视频源控制方式
static char  WHAT_SET_VIDEO_SOURCE_CONTROL_MODE = (char)0xA3;
//设置视频源分辨率
static char  WHAT_SET_VIDEO_SOURCE = (char)0xA4;
//设置内部视频源分辨率
static char WHAT_SET_INTERNAL_VIDEO_SOURCE = (char)0xA5;
//获取内部视频源分辨率
static char WHAT_GET_INTERNAL_VIDEO_SOURCE = (char)0xA6;
//获取所有播放列表id
static char  WHAT_GET_ALL_PLAYLIST_ID = (char)0xA7;
//获取cpu和内存使用率
static char WHAT_GET_CPU_AND_MEMORY_RATE = (char)0xAF;

static int SUCCESS = 1;
static int UNKNOWN_HOST = -1;
static int IO_ERROR = -2;
static int SEND_FILE_NAME_NOT_RECV_ERROR = -3;
static int SEND_FILE_NAME_RECV_ERROR = -4;
static int SEND_FILE_BLOCK_NOT_RECV_ERROR = -5;
static int SEND_FILE_BLOCK_RECV_ERROR = -6;
static int SEND_FILE_BLOCK_NOT_RECV_END_ERROR = -7;
static int SEND_FILE_BLOCK_RECV_END_ERROR = -8;
static int PLAY_LIST_NOT_RECV_ERROR = -9;
static int PLAY_LIST_RECV_ERROR = -10;
static int SEND_NOT_RECV_ERROR = -11;
static int SEND_RECV_ERROR = -12;
static int FILE_NOT_EXIST_ERROR = -13;
static int SOCKET_ERROR = -14;
static int PARAM_ERROR = -15;

static bool openDebug = true;
extern void intToBytes(char* buffer, int offset, int value);
extern short pubCalcCRC(char* bytes, int len);
extern short bytesToShort(char* buffer, int offset);
extern void shortToBytes(char* buffer, int offset, short value);
extern void normalIntToBytes(char* buffer, int offset, int value);
extern int ipToInt(const string& strIP);
extern int bytesToInt(char* buffer, int offset);
extern const vector<string> split(const string& s, const char& c);
extern tm getTm(int year, int  month, int  day, int  hour, int  minute, int  second);
extern char* makeSendPacketEx(char what, char* data, int dataSize,bool des,char* key, int* outSize);
extern void printfHexCharArray(char* text, unsigned char* data);
// std::string 转换为 UTF - 8 编码
extern bool string_To_Bool(const string& str);
//通用的delete方法
extern void deleteObj(void** p);
extern void deleteArry(void** p);
