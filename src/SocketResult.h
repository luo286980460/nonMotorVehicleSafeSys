#pragma once
#include <string.h>
class SocketResult
{
public:
	SocketResult(char* data, int len);
	~SocketResult();
	char* toStrChar(int start);
	char* getOrgChar();
	int getLen();
private:
	static const int SUCCESS = 1;
	int len;
	char* data;
	bool isSuccesed(int minLen);
};