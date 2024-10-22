#ifndef MYMAIN_H
#define MYMAIN_H

#include <QObject>

class MyHttpServer;
class GPS;

class MyMain : public QObject
{
    Q_OBJECT
public:
    explicit MyMain(QObject *parent = nullptr);

private:
    void loadIni();
    void initMyHttpServer(int NonMotorVehicleSafeSysPort, int NovaScreenServerPort);
    void initGps(QString GpsPortName, QString GpsUrl);

signals:

public slots:
    void showMsg(QString msg);

private:
    MyHttpServer* myHttpServer;
    GPS* m_GPS;
};

#endif // MYMAIN_H
