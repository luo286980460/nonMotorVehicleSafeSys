#ifndef MYHTTPSERVERWORKER_H
#define MYHTTPSERVERWORKER_H

#include "include/libhv/HttpServer.h"

#include <QObject>

class MyHttpServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyHttpServerWorker(QObject *parent = nullptr);
    ~MyHttpServerWorker();

signals:

public slots:
    void slotStart();

private:
    int m_port = 23333;
    hv::HttpService m_router;
    hv::HttpServer m_server;
};

#endif // MYHTTPSERVERWORKER_H
