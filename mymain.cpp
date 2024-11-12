#include <QSettings>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDebug>

#include "mymain.h"
#include "gps.h"
#include "myhttpserver.h"
#include "novacontroller.h"

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
    QString Face2BackUrl;
    QString Face2BoxUrl;
    QString NovaScreenIp;
    QString Place;
    int BackToDefTime;

    QString iniPath = QCoreApplication::applicationDirPath() + INIFILE_PORT;
    if(!QFileInfo::exists(iniPath)){
        showMsg("****** cfg.ini 配置文件丢失 ******");
        return;
    }

    QSettings settings(iniPath, QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    NonMotorVehicleSafeSysPort = settings.value("Port/NonMotorVehicleSafeSysPort", -1).toInt();
    NovaScreenServerPort = settings.value("Port/NovaScreenServerPort", -1).toInt();
    GpsPortName = settings.value("Url/GpsPortName", "-1").toString();
    GpsUrl = settings.value("Url/GpsUrl", "-1").toString();
    Face2BackUrl = settings.value("Url/Face2BackUrl", "-1").toString();
    Face2BoxUrl = settings.value("Url/Face2BoxUrl", "-1").toString();
    NovaScreenIp = settings.value("Nova/NovaScreenIp", "-1").toString();
    BackToDefTime = settings.value("Nova/BackToDefTime", -1).toInt();
    Place = settings.value("Url/Place", "-1").toString();

    if(NonMotorVehicleSafeSysPort < 1 || NovaScreenServerPort < 1  || Face2BackUrl == "-1"  || Face2BoxUrl == "-1"){
        showMsg("****** cfg.ini NonMotorVehicleSafeSysPort < 1 || NovaScreenServerPort < 1  || Face2BackUrl == -1  || Face2BoxUrl == -1******");
        return;
    }else{
        initMyHttpServer(NonMotorVehicleSafeSysPort, NovaScreenServerPort, Face2BackUrl, Face2BoxUrl, Place);
    }

    if(GpsPortName == "-1" || GpsUrl == "-1"){
        showMsg("****** cfg.ini GpsPortName == -1 || GpsUrl == -1  || FaceUrl == -1 ");
        return;
    }else{
        initGps(GpsPortName, GpsUrl);
    }

    if(NovaScreenIp == "-1" || BackToDefTime == -1){
        showMsg("****** cfg.ini NovaScreenIp == -1 || BackToDefTime == -1");
        return;
    }else{
        initNovaController(NovaScreenIp, BackToDefTime);
    }

    if(m_myHttpServer && m_NovaController){
        connect(m_myHttpServer, &MyHttpServer::signalPlayProgram1, m_NovaController, &NovaController::signalPlayProgram1);
        connect(m_myHttpServer, &MyHttpServer::signalPlayProgram2, m_NovaController, &NovaController::signalPlayProgram2);
        connect(m_myHttpServer, &MyHttpServer::signalPlayProgram3, m_NovaController, &NovaController::signalPlayProgram3);
        connect(m_myHttpServer, &MyHttpServer::signalSetDefaultTxt, m_NovaController, &NovaController::signalSetDefaultTxt);
        connect(m_myHttpServer, &MyHttpServer::signalSetDefaultPic, m_NovaController, &NovaController::signalSetDefaultPic);
        connect(m_myHttpServer, &MyHttpServer::signalSetCurrentDefaultProgram, m_NovaController, &NovaController::signalSetCurrentDefaultProgram);
    }
}

void MyMain::initMyHttpServer(int NonMotorVehicleSafeSysPort, int NovaScreenServerPort, QString Face2BackUrl, QString Face2BoxUrl, QString Place)
{
    m_myHttpServer = new MyHttpServer(NonMotorVehicleSafeSysPort, NovaScreenServerPort, Face2BackUrl, Face2BoxUrl, Place);

    m_myHttpServer->start();
}

void MyMain::initNovaController(QString ip, int backToDefTime)
{
    m_NovaController = new NovaController(ip, backToDefTime);
    m_NovaController->start();
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
