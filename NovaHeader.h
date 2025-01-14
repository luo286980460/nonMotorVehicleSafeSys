#ifndef NOVAHEADER_H
#define NOVAHEADER_H

/*
 * 节目1 文字节目
 * 页面数量：1
 * 第一页内容：默认节目图片
 *  %1 字号
 *  %2 文字内容
 *  %3 语音播放次数
 *  %4 语音播放内容
 *  %5 语音是否开启 1开 0关闭
 *  %6 语音 音量 1-9
*/
#define PROGRAM1 "\
[all]\r\n\
items=1\r\n\
[item1]\r\n\
param=100,1,1,1,0,5,1\r\n\
txtext1=0,0,160,240,微软雅黑,%1,0,2,2,0,0,ff0000,00000000,0,1,1410065398,1,%2,0,0,0,0,5,5\r\n\
txtext2=80,0,400,240,微软雅黑,1,0,1,2,0,0,ff0000,00000000,0,1,1410065398,%3,%4,%5,0,0,%6,5,5\r\n\
info=160,240"


//#define PROGRAM1_ITEM1_PIC "Program1Item1Pic.jpg"

/*
 * 节目2 图片节目
 * 页面数量：1
 * 第一页内容：节目图片
 *  %1 图片名
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

*/
#define PROGRAM3 "\
[all]\r\n\
items=1\r\n\
[item1]\r\n\
param=1410065398,1,1,1,0,5,1\r\n\
txtext1=0,0,160,80,微软雅黑,%1,0,2,2,0,0,ff0000,00000000,0,1,1410065398,1,%2,0,0,0,0,5,5\r\n\
txtext2=80,0,400,240,微软雅黑,1,0,1,2,0,0,ff0000,00000000,0,1,1410065398,%3,%4,%5,0,0,%6,5,5\r\n\
img3=0,80,%7,0,160,160\r\n\
imgparam3=1410065398\r\n\
info=160,240"

//txtext3=161,1,10,10,微软雅黑,1,0,2,2,0,0,ff0000,00000000,1,1,1410065390,1,请戴好头盔,1,0,0,1,3,5

#define PROGRAM_DEF "\
[all]\r\n\
items=1\r\n\
[item1]\r\n\
param=100,1,1,1,0,5,1\r\n\
img1=0,0,default.png,0,160,240\r\n\
imgparam1=100\r\n\
info=160,240"

#endif // NOVAHEADER_H
