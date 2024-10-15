#pragma once
#include "NovaUtils.h"
class DeviceNowPlayItem
{
private :
	bool isOpen;
	int playId;
	char* content;
public:
	DeviceNowPlayItem(bool isOpen, int playId, char* content);
	~DeviceNowPlayItem();
	bool playIsOpen();
	int getPlayId();
	char* getContent();
};

