#include "mymain.h"

#include <QCoreApplication>

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
 *      主服务端口：23333
 *      音频服务端口：23334
 *      诺瓦服务端口：23335
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    MyMain myMain;

    return a.exec();
}
