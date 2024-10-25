#ifndef MYMAIN_H
#define MYMAIN_H

#include <QObject>

class MyHttpServer;
class NovaController;
class GPS;

class MyMain : public QObject
{
    Q_OBJECT
public:
    explicit MyMain(QObject *parent = nullptr);

private:
    void loadIni();
    void initMyHttpServer(int NonMotorVehicleSafeSysPort, int NovaScreenServerPort, QString Face2BackUrl, QString Face2BoxUrl);
    void initNovaController(QString ip);
    void initGps(QString GpsPortName, QString GpsUrl);

signals:
    void signalPlayProgram1(int fontSize, QString content, int audioTimes, QString voiceContent, int audioSwitch, int audiovolume);

public slots:
    void showMsg(QString msg);

private:
    MyHttpServer* m_myHttpServer
        = nullptr;
    NovaController* m_NovaController
        = nullptr;
    GPS* m_GPS;
};

#endif // MYMAIN_H
