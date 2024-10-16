#ifndef MYHTTPSERVERWORKER_H
#define MYHTTPSERVERWORKER_H

#include "include/libhv/HttpServer.h"

#include <QObject>
#include <QNetworkAccessManager>

class MyHttpServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyHttpServerWorker(QObject *parent = nullptr);
    ~MyHttpServerWorker();

private:
    QJsonDocument unpackNonMotorVehicleIllegalInfo(QJsonObject& json);
    //void post(QString url, QByteArray& data);
    void postBack(QNetworkReply* reply);

signals:
    void signalPost(QString url, QByteArray data);

public slots:
    void slotStart();
    void post(QString url, QByteArray data);

private:
    int m_port = 23333;
    hv::HttpService m_router;
    hv::HttpServer m_server;
    QString m_imgSavePath;
    QNetworkAccessManager* m_manager;    // 网络请求管理
    QString m_aPlayerIpPort;
    QString m_novaScreenIpPort;
};

#endif // MYHTTPSERVERWORKER_H
