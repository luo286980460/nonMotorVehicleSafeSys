#pragma once

#include <iostream>
#include <string>
#include "NovaUtils.h"

extern char* readFile(char* fileName);
extern void writeFileAppend(const char* fileName, const char* buffer, streamsize len);
//文件存在则清空，不存在则创建新文件
extern bool createEmptyFile(const char* filename);


