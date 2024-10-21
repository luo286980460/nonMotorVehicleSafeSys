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

private:
    QJsonDocument unpackNonMotorVehicleIllegalInfo(QJsonObject& json);
    QJsonDocument unpackPlayProgram1(QJsonObject& json);
    QJsonDocument unpackPlayProgram2(QJsonObject& json);
    QJsonDocument unpackPlayProgram3(QJsonObject& json);
    //QJsonDocument unpackPlayProgramOff(QJsonObject& json);

signals:
    void signalPlayProgram1(int fontSize, QString content, int audioTimes, QString voiceContent, int audioSwitch, int audiovolume);
    void signalPlayProgram2(QString base64);
    void signalPlayProgram3(int fontSize, QString content, int audioTimes, QString voiceContent,
                            int audioSwitch, int audiovolume , QString base64);

public slots:
    void slotStart();

private:
    int m_port = 23335;
    hv::HttpService m_router;
    hv::HttpServer m_server;
    QString m_imgSavePath;
};

#endif // MYHTTPSERVERWORKER_H
