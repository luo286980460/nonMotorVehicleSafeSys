#include "mymainclass.h"
#include "myhttpserver.h"
#include "novacontroller.h"

#include <QDebug>


MyMainClass::MyMainClass(QObject *parent)
    : QObject{parent}
{
    initNovaController();
    initMyHttpServer();

    connect(myHttpServer, &MyHttpServer::signalPlayProgram1, m_NovaController, &NovaController::signalPlayProgram1);
    connect(myHttpServer, &MyHttpServer::signalPlayProgram2, m_NovaController, &NovaController::signalPlayProgram2);
    connect(myHttpServer, &MyHttpServer::signalPlayProgram3, m_NovaController, &NovaController::signalPlayProgram3);
}

void MyMainClass::initNovaController()
{
    m_NovaController = new NovaController("192.168.1.176", 5);
    m_NovaController->start();
}

void MyMainClass::initMyHttpServer()
{
    myHttpServer = new MyHttpServer();

    myHttpServer->start();
}
