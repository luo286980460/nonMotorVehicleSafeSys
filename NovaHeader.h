#ifndef NOVAHEADER_H
#define NOVAHEADER_H

/*
 * 节目1 文字节目
 * 页面数量：1
 * 第一页内容：默认节目图片
 *  %1 字号
 *  %2 内容
*/
#define PROGRAM1 "\
[all]\r\n\
items=1\r\n\
[item1]\r\n\
param=100,1,1,1,0,5,1\r\n\
txtext1=0,0,160,240,微软雅黑,%1,0,2,2,0,0,ff0000,00000000,0,1,100,1,%2,0,0,0,0,0,0\r\n\
info=160,240"

//#define PROGRAM1_ITEM1_PIC "Program1Item1Pic.jpg"

/*
 * 节目2 图片节目
 * 页面数量：1
 * 第一页内容：节目图片
 *  %1 字号
 *  %2 内容
*/

#define PROGRAM2 "\
[all]\r\n\
items=1\r\n\
[item1]\r\n\
param=100,1,1,1,0,5,1\r\n\
img1=0,0,%1,0,160,240\r\n\
imgparam1=100\r\n\
info=160,240"

//#define PROGRAM2_ITEM1_PIC "Program2I%1tem1Pic.jpg"

/*
 * 节目3 违法节目
 * 页面数量：1
 * 第一页内容：违法照片
 * 第一页内容：默认违法节目图片
*/
#define PROGRAM3 "\
[all]\r\n\
items=1\r\n\
[item1]\r\n\
param=100,1,1,1,0,5,1\r\n\
txtext1=0,0,160,80,微软雅黑,%1,0,2,2,0,0,ff0000,00000000,0,1,100,1,%2,0,0,0,0,0,0\r\n\
img2=0,80,%3,0,160,160\r\n\
imgparam2=100\r\n\
info=160,240"

#endif // NOVAHEADER_H
