#ifndef MYHTTPSERVERWORKER_H
#define MYHTTPSERVERWORKER_H

#include <QObject>

#include "include/HttpServer.h"

using namespace hv;

class aPlayer;

class MyHttpServerWorker : public QObject
{
    Q_OBJECT
public:


    explicit MyHttpServerWorker(QObject *parent = nullptr);
    ~MyHttpServerWorker();

private:
    void initHttpServer();
    void initAPlayer();

signals:
    //void showMsg(QString msg);
    void signalPlayStart();
    void signalPlayStop();
    void signalClearPlayListp();

public slots:
    void slotStart();

private:
    HttpServer* m_server = nullptr;
    HttpService* m_router = nullptr;
    int m_port = 8888;
    aPlayer* m_aPlayer = nullptr;
};

#endif // MYHTTPSERVERWORKER_H
