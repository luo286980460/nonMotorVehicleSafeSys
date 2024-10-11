#include "mymain.h"
#include "myhttpserver.h"

MyMain::MyMain(QObject *parent)
    : QObject{parent}
{
    initMyHttpServer();
}

void MyMain::initMyHttpServer()
{
    myHttpServer = new MyHttpServer();

    myHttpServer->start();
}
