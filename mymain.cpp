#include <QSettings>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDebug>

#include "mymain.h"
#include "gps.h"
#include "myhttpserver.h"

#define INIFILE_PORT         "/cfg.ini"

MyMain::MyMain(QObject *parent)
    : QObject{parent}
{
    loadIni();
}

void MyMain::loadIni()
{
    int NonMotorVehicleSafeSysPort;
    int NovaScreenServerPort;
    QString GpsPortName;
    QString GpsUrl;

    QString iniPath = QCoreApplication::applicationDirPath() + INIFILE_PORT;
    if(!QFileInfo::exists(iniPath)){
        showMsg("****** cfg.ini 配置文件丢失 ******");
        return;
    }
    QSettings settings(iniPath, QSettings::IniFormat);
    NonMotorVehicleSafeSysPort = settings.value("Port/NonMotorVehicleSafeSysPort", -1).toInt();
    NovaScreenServerPort = settings.value("Port/NovaScreenServerPort", -1).toInt();
    GpsPortName = settings.value("Url/GpsPortName", "-1").toString();
    GpsUrl = settings.value("Url/GpsUrl", "-1").toString();

    if(NonMotorVehicleSafeSysPort < 1 || NovaScreenServerPort < 1){
        showMsg("****** cfg.ini NonMotorVehicleSafeSysPort < 1 || NovaScreenServerPort < 1 ******");
    }else{
        initMyHttpServer(NonMotorVehicleSafeSysPort, NovaScreenServerPort);
    }

    if(GpsPortName == "-1" || GpsUrl == "-1" ){
        showMsg("****** cfg.ini GpsPortName == -1 || GpsUrl == -1 ");
    }else{
        initGps(GpsPortName, GpsUrl);
    }
}

void MyMain::initMyHttpServer(int NonMotorVehicleSafeSysPort, int NovaScreenServerPort)
{
    myHttpServer = new MyHttpServer(NonMotorVehicleSafeSysPort, NovaScreenServerPort);

    myHttpServer->start();
}

void MyMain::initGps(QString GpsPortName, QString GpsUrl)
{
    m_GPS = new GPS(GpsPortName, GpsUrl, this);
    connect(m_GPS, &GPS::showMsg, this, &MyMain::showMsg);
}

void MyMain::showMsg(QString msg)
{
    qDebug() << msg;
}
