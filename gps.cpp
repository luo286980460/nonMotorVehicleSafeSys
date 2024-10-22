#include <QSerialPortInfo>
#include <QDebug>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include "gps.h"

GPS::GPS(QString GpsPortName, QString GpsUrl, QObject *parent)
    : QObject{parent}
    , m_GgpsUrl(GpsUrl)
{
    m_manager = new QNetworkAccessManager;
    init(GpsPortName);
    initTimer();
}

void GPS::initTimer()
{
    m_timer = new QTimer(this);
    m_timer->setInterval(3600000);

    connect(m_timer, &QTimer::timeout, this, [this]{
        // if(QDateTime::currentDateTime().toString("mm:ss") == "00:00"){
        //     // 整点发送位置信息
        //     QJsonObject jsonObj;

        //     if(m_BDGGA.size() == 14){
        //         jsonObj.insert(m_BDGGA.at(2) == "N" ? "北纬" : "南纬", m_BDGGA.at(1));
        //         jsonObj.insert(m_BDGGA.at(4) == "E" ? "东经" : "西经", m_BDGGA.at(3));

        //         post(m_GgpsUrl, QJsonDocument(jsonObj).toJson());
        //     }
        // }

            // 发送位置信息
            QJsonObject jsonObj;

            //qDebug() << "m_BDGGA.size(): " << m_BDGGA.size();

            if(m_BDGGA.size() == 14){
                jsonObj.insert(m_BDGGA.at(2) == "N" ? "北纬" : "南纬", m_BDGGA.at(1));
                jsonObj.insert(m_BDGGA.at(4) == "E" ? "东经" : "西经", m_BDGGA.at(3));
                post(m_GgpsUrl, QJsonDocument(jsonObj).toJson());
            }

    });

    m_timer->start();
}

void GPS::init(QString GpsPortName)
{
    m_GPS = new QSerialPort;
    connect(m_GPS, &QSerialPort::readyRead, this, &GPS::slotUnPackData);

    foreach (QSerialPortInfo portInfo, QSerialPortInfo::availablePorts()) {
        qDebug() << (portInfo.portName());
        if(portInfo.portName() == GpsPortName){
            m_GPS->setPort(portInfo);
        }
    }

    m_GPS->setBaudRate(QSerialPort::Baud115200);


    if(m_GPS->open(QIODevice::ReadWrite)){
        qDebug() << ("GPS 打开成功");
    }else{
        qDebug() << ("GPS 打开失败");
    }
}

bool GPS::getFirstData(QByteArray& data, QByteArray& first)
{
    // 去除串头可能出现的其他字符
    while(data.size() > 0 && data[0] != '$'){
        data.remove(0, 1);
    }

    for(int i=0; i<data.size(); i++){

        if(data.at(i) == '\r'){
            data.remove(0, i+1);
            return true;
        }

        first.append(data.at(i));
    }
    return false;
}

void GPS::unPackBDGGA(QString BDGGA)
{
    s_BDGGA bdgga;
    m_BDGGA = BDGGA.split(",");
    if(m_BDGGA.size() != 15){
        return;
    }

    m_BDGGA.removeFirst();
}

void GPS::post(QString url, QByteArray data)
{
    // 构造请求
    QNetworkRequest request;
    /*httpbin.org 这个网站能测试 HTTP 请求和响应的各种信息，比如 cookie、ip、headers 和登录验证等，且支持 GET、POST 等多种方法，对 web 开发和测试很有帮助。*/
    request.setUrl(QUrl(url));

    //request.setUrl(QUrl("http://10.181.218.209:8080/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // 发送请求
    m_manager->post(request, data);
}

void GPS::slotUnPackData()
{
    m_dataTmp += m_GPS->readAll();
    QByteArray ba1;


    while(getFirstData(m_dataTmp, ba1)){
        ba1 = ba1.trimmed();
        if(QString(ba1).contains("$BDGGA")){
            unPackBDGGA(QString(ba1));
            //qDebug() << "m_BDGGA:" << m_BDGGA;
        }
        ba1.clear();
    }

}
