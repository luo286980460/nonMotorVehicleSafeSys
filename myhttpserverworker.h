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
    explicit MyHttpServerWorker(int port, int novaScreen, QString face2BackUrl, QString face2BoxUrl, QString Place, QObject *parent = nullptr);
    ~MyHttpServerWorker();

private:
    QJsonDocument unpackNonMotorVehicleIllegalInfo(QJsonObject& json);
    //void post(QString url, QByteArray& data);
    void postBack(QNetworkReply* reply);
    QString img2base64(QImage image);
    QJsonDocument unpackPlayProgram1(QJsonObject& json, int type);  // type:1-播放节目  type:2-修改默认节目数据
    QJsonDocument unpackPlayProgram2(QJsonObject& json, int type);
    QJsonDocument unpackPlayProgram3(QJsonObject& json);

    void sendToBackServer(QJsonObject& json);   // 发送给后台

signals:
    void signalPost(QString url, QByteArray data);
    void signalPlayProgram1(int fontSize, QString content, int audioTimes, QString voiceContent, int audioSwitch, int audiovolume);
    void signalPlayProgram2(QString base64);
    void signalPlayProgram3(int fontSize, QString content, int audioTimes, QString voiceContent,
                            int audioSwitch, int audiovolume , QString base64);
    void signalSetDefaultTxt(QString content);    // 设置默认节目的内容
    void signalSetDefaultPic(QString base64);     // 设置默认节目的图片
    void signalSetCurrentDefaultProgram(int currentProgram);    // 设置当前默认节目的图片编号


public slots:
    void slotStart();
    void post(QString url, QByteArray data);

private:
    int m_port;
    int m_novaScreen;
    hv::HttpService m_router;
    hv::HttpServer m_server;
    QString m_imgSavePath;
    QNetworkAccessManager* m_manager;    // 网络请求管理
    QString m_aPlayerIpPort;
    QString m_novaScreenIpPort;
    QString m_face2BackUrl;
    QString m_face2BoxUrl;
    QString m_place;
};

#endif // MYHTTPSERVERWORKER_H
