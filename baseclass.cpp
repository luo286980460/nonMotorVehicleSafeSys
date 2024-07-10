#include "baseclass.h"
#include "myhttpserverworker.h"


baseClass::baseClass(QObject *parent)
    : QObject{parent}
{
    initMyHttpServer();
}

void baseClass::initMyHttpServer()
{
    m_myHttpServer = new MyHttpServerWorker();
    m_myHttpServer->slotStart();
    //m_myHttpServer->start();

}
