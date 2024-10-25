#pragma once
#include "NovaUtils.h"
class DeviceNowPlayList
{
private: int playId;
		char* content;
public :
	DeviceNowPlayList(int playId, char* content);
	~DeviceNowPlayList();
	int getPlayId();
	char* getContent();
};

