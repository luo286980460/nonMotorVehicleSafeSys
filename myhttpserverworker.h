#ifndef MYHTTPSERVERWORKER_H
#define MYHTTPSERVERWORKER_H

#include "include/libhv/HttpServer.h"

#include <QObject>
#include <QNetworkAccessManager>

typedef enum{       // 30号字体 最多5字   最多6行
    all,
    withoutHelmet,      // 第一行：姓名 第二行：请带好头盔 识别不出的的只显示第二行    回车
    manned,             // 请不要违法载人                                      不加回车
    retrograde,         // 请不要逆行                                        回车
    jiZhanFei           // 第一行：车牌 第二行：违法占道
}e_illegalAct;

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
    QString img2base64(QImage image);

    void sendToBackServer(QJsonObject& json);   // 发送给后台

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
