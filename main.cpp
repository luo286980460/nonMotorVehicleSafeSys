#include <QCoreApplication>
#include "baseclass.h"

/*
 * 环境：
 *      Distributor ID: Ubuntu
 *      Description:    Ubuntu 22.04.2 LTS
 *      Release:        22.04
 *      Codename:       jammy
 *
 * 编译器：
 *      QMake version 3.1
 *      Using Qt version 5.15.3
 *
 * 动态库：
 *      libhv.so
 *
 *  端口：
 *      音频服务端口：23334
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    baseClass base;

    return a.exec();
}
