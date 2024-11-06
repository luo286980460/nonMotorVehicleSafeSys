#include "myhttpserver.h"
#include "myhttpserverworker.h"

MyHttpServer::MyHttpServer(int port, int novaScreen, QString face2BackUrl, QString face2BoxUrl, QString Place, QObject *parent)
    : QObject{parent}
{
    m_work = new MyHttpServerWorker(port, novaScreen, face2BackUrl, face2BoxUrl, Place);

    m_work->moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::finished, m_work, &QObject::deleteLater);
    connect(this, &MyHttpServer::signalStart, m_work, &MyHttpServerWorker::slotStart);
    connect(m_work, &MyHttpServerWorker::signalPlayProgram1, this, &MyHttpServer::signalPlayProgram1);
    connect(m_work, &MyHttpServerWorker::signalPlayProgram2, this, &MyHttpServer::signalPlayProgram2);
    connect(m_work, &MyHttpServerWorker::signalPlayProgram3, this, &MyHttpServer::signalPlayProgram3);
}

MyHttpServer::~MyHttpServer()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

void MyHttpServer::start()
{
    m_workerThread.start();
    emit signalStart();
}

void MyHttpServer::stop()
{
    m_workerThread.quit();
    m_workerThread.wait();
}
