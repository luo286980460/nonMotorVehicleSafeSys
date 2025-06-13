#include <QSettings>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDebug>

#include "mymain.h"
#include "gps.h"
#include "myhttpserverworker.h"
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
    QString ImgPathHead;
    int BackToDefTime;
    int score;

    QString iniPath = QCoreApplication::applicationDirPath() + INIFILE_PORT;
    if(!QFileInfo::exists(iniPath)){
        showMsg("****** cfg.ini 配置文件丢失 ******");
        return;
    }

    QSettings settings(iniPath, QSettings::IniFormat);
    settings.setIniCodec("utf-8");
    NonMotorVehicleSafeSysPort = settings.value("Port/NonMotorVehicleSafeSysPort", -1).toInt();
    NovaScreenServerPort = settings.value("Port/NovaScreenServerPort", -1).toInt();
    score = settings.value("Port/Score", -1).toInt();
    GpsPortName = settings.value("Url/GpsPortName", "-1").toString();
    GpsUrl = settings.value("Url/GpsUrl", "-1").toString();
    Face2BackUrl = settings.value("Url/Face2BackUrl", "-1").toString();
    Face2BoxUrl = settings.value("Url/Face2BoxUrl", "-1").toString();
    NovaScreenIp = settings.value("Nova/NovaScreenIp", "-1").toString();
    BackToDefTime = settings.value("Nova/BackToDefTime", -1).toInt();
    Place = settings.value("Url/Place", "-1").toString();
    ImgPathHead = settings.value("Url/ImgPathHead", "-1").toString();
    //qDebug() << "-----------------------------------ImgPathHead: " << ImgPathHead;

    if(NonMotorVehicleSafeSysPort < 1 || NovaScreenServerPort < 1  || Face2BackUrl == "-1"  || Face2BoxUrl == "-1"){
        showMsg("****** cfg.ini NonMotorVehicleSafeSysPort < 1 || NovaScreenServerPort < 1  || Face2BackUrl == -1  || Face2BoxUrl == -1******");
        return;
    }else{
        initMyHttpServer(NonMotorVehicleSafeSysPort, NovaScreenServerPort, Face2BackUrl, Face2BoxUrl, Place, ImgPathHead, score);
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
        connect(m_myHttpServer, &MyHttpServerWorker::signalPlayProgram1, m_NovaController, &NovaController::signalPlayProgram1);
        connect(m_myHttpServer, &MyHttpServerWorker::signalPlayProgram2, m_NovaController, &NovaController::signalPlayProgram2);
        connect(m_myHttpServer, &MyHttpServerWorker::signalPlayProgram3, m_NovaController, &NovaController::signalPlayProgram3);
        connect(m_myHttpServer, &MyHttpServerWorker::signalSetDefaultTxt, m_NovaController, &NovaController::signalSetDefaultTxt);
        connect(m_myHttpServer, &MyHttpServerWorker::signalSetDefaultPic, m_NovaController, &NovaController::signalSetDefaultPic);
        connect(m_myHttpServer, &MyHttpServerWorker::signalSetCurrentDefaultProgram, m_NovaController, &NovaController::signalSetCurrentDefaultProgram);
    }
}

void MyMain::initMyHttpServer(int NonMotorVehicleSafeSysPort, int NovaScreenServerPort, QString Face2BackUrl, QString Face2BoxUrl, QString Place, QString ImgPathHead, int score)
{
    m_myHttpServer = new MyHttpServerWorker(NonMotorVehicleSafeSysPort, NovaScreenServerPort, Face2BackUrl, Face2BoxUrl, Place, ImgPathHead, score);

    //m_myHttpServer->start();
    m_myHttpServer->slotStart();
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
