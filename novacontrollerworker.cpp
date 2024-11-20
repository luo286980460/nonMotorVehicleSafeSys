#include <QApplication>
#include <QImage>
#include <QDebug>
#include <QDateTime>
#include <QDir>

#include "novacontrollerworker.h"
#include "include/Nova/NovaTraffic.h"
#include "NovaHeader.h"

#define ILLEGAL_PIC_NAME "/illegal.jpg"
#define DEFAULT_PIC_NAME "/default.png"

NovaControllerWorker::NovaControllerWorker(QString ip, int Back2DefaultProgram, QObject *parent)
    : QObject{parent}
    , m_ip(ip)
    , m_port(5000)
    , m_Back2DefaultProgramTime(Back2DefaultProgram)
    , m_Back2DefaultProgramTimeFlag(Back2DefaultProgram)
{
    m_illegalPicPath = QApplication::applicationDirPath() + "/Pics";
    QDir dir(m_illegalPicPath);
    if(!dir.exists()){
        dir.mkpath(m_illegalPicPath);
    }
}

void NovaControllerWorker::PlayProgramDefault()
{
    switch (m_currentDef) {
    case 1:
        PlayProgramDefaultTxt();
        break;
    case 2:
        PlayProgramDefaultPic();
        break;
    case 3:
        PlayProgramDefaultTxtAndPic();
        break;
    default:
        m_currentDef = 3;
        PlayProgramDefaultTxtAndPic();
        break;
    }
}

void NovaControllerWorker::PlayProgramDefaultTxt()
{
    char* program = QString(PROGRAM1)
                        .arg(m_defaultTxtSize)
                        .arg(m_defaultTxt)
                        .arg(1)
                        .arg(" ")
                        .arg(0)
                        .arg(1)
                        .toLocal8Bit().data();
    m_traffic->sendPlayList(1, program);
    m_playFlag = 0;
}

void NovaControllerWorker::PlayProgramDefaultPic()
{
    char* program = QString(PROGRAM2).arg(DEFAULT_PIC_NAME).toLocal8Bit().data();
    m_traffic->sendPlayList(1, program);
    m_playFlag = 0;
}

void NovaControllerWorker::PlayProgramDefaultTxtAndPic()
{
    char* program = QString(PROGRAM3)
                        .arg(m_defaultTxtSize)
                        .arg(m_defaultTxt)
                        .arg(1)
                        .arg(" ")
                        .arg(0)
                        .arg(1)
                        .arg(DEFAULT_PIC_NAME).toLocal8Bit().data();
    m_traffic->sendPlayList(1, program);
    m_playFlag = 0;
}

// void NovaControllerWorker::playProgram1()
// {
//     // 下发文件
//     int res = m_traffic->sendFile((QApplication::applicationDirPath() + "/Pics/" + PROGRAM1_ITEM1_PIC).toLocal8Bit(),
//                                   QString(PROGRAM1_ITEM1_PIC).toLocal8Bit());

//     //emit showMsg(QString("playProgram1() sendFile res = %1").arg(res));

//     // 发送节目
//     char program[] = PROGRAM1;
//     res = m_traffic->sendPlayList(1, program);

//     //emit showMsg(QString("playProgram1() sendPlayList res = %1").arg(res));
// }

// void NovaControllerWorker::playProgram2()
// {
//     // 下发文件
//     int res = m_traffic->sendFile((QApplication::applicationDirPath() + "/Pics/" + PROGRAM2_ITEM1_PIC).toLocal8Bit(),
//                                   QString(PROGRAM2_ITEM1_PIC).toLocal8Bit());

//     //emit showMsg(QString("playProgram2() sendFile res = %1").arg(res));

//     // 发送节目
//     char program[] = PROGRAM2;
//     m_traffic->sendPlayList(2, program);

//     //emit showMsg(QString("playProgram1() sendPlayList res = %1").arg(res));
// }

// void NovaControllerWorker::playProgram3()
// {
//     // 下发文件 1
//     int res = m_traffic->sendFile((QApplication::applicationDirPath() + "/Pics/" + PROGRAM3_ITEM1_PIC).toLocal8Bit(),
//                                   QString(PROGRAM3_ITEM1_PIC).toLocal8Bit());

//     //emit showMsg(QString("playProgram3() sendFile1 res = %1").arg(res));

//     // 下发文件 2
//     res = m_traffic->sendFile((QApplication::applicationDirPath() + "/Pics/" + PROGRAM3_ITEM2_PIC).toLocal8Bit(),
//                               QString(PROGRAM3_ITEM2_PIC).toLocal8Bit());

//     //emit showMsg(QString("playProgram3() sendFile2 res = %1").arg(res));

//     // 发送节目
//     char program[] = PROGRAM3;
//     m_traffic->sendPlayList(3, program);

//     //emit showMsg(QString("playProgram1() sendPlayList res = %1").arg(res));
// }

void NovaControllerWorker::slotInit()
{
    m_traffic = new NovaTraffic(m_ip.toLocal8Bit(), m_port);

    // 播放节目1 默认节目
    PlayProgramDefault();

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, [=](){
        //showMsg(QString("m_playFlag:%1 m_ProgramInterval:%2 ").arg(m_playFlag).arg(m_ProgramInterval));
        //showMsg(QString("m_Back2DefaultProgramTimeFlag:%1 m_Back2DefaultProgramTime:%2 ").arg(m_Back2DefaultProgramTimeFlag).arg(m_Back2DefaultProgramTime));
        if(m_playFlag < m_ProgramInterval){         // 不能发送节目
            m_playFlag++;
            if(m_Back2DefaultProgramTimeFlag < m_Back2DefaultProgramTime){    // 等待发送节目
                m_Back2DefaultProgramTimeFlag++;
            }

        }else if(m_playFlag == m_ProgramInterval){  // 可发送节目
            if(m_Back2DefaultProgramTimeFlag == m_Back2DefaultProgramTime){
                // 播放节目1 默认节目
                PlayProgramDefault();
                m_Back2DefaultProgramTimeFlag++;
            }else if(m_Back2DefaultProgramTimeFlag < m_Back2DefaultProgramTime){    // 等待发送节目
                m_Back2DefaultProgramTimeFlag++;
            }
        }
    });
    m_timer->start();
}

void NovaControllerWorker::slotPlayProgram1(int fontSize, QString content, int audioTimes
                                            , QString voiceContent, int audioSwitch, int audiovolume)
{
    char* program = QString(PROGRAM1)
                        .arg(fontSize)
                        .arg(content)
                        .arg(audioTimes)
                        .arg(voiceContent)
                        .arg(audioSwitch)
                        .arg(audiovolume)
                        .toLocal8Bit().data();

    //qDebug() << "\n************************************************************************************************************************";
    //qDebug() << "********** sendPlayList " + QDateTime::currentDateTime().toString("进： yyyyMMdd hh:mm:ss.zzz");

    int res = m_traffic->sendPlayList(1, program);

    //qDebug() << "********** sendPlayList " + QDateTime::currentDateTime().toString("出： yyyyMMdd hh:mm:ss.zzz");
    //qDebug() << "************************************************************************************************************************\n";
    m_playFlag = 0;
    m_Back2DefaultProgramTimeFlag = 0;
}

void NovaControllerWorker::slotPlayProgram2(QString base64)
{
    QByteArray img = QByteArray::fromBase64(base64.toLocal8Bit());
    QImage image;
    image.loadFromData(img);

    // 保存图片并且上屏
    if(!base64.isEmpty()){
        image.save(m_illegalPicPath + ILLEGAL_PIC_NAME, "jpg", m_imgSaveLevel);
        qDebug() << m_illegalPicPath + ILLEGAL_PIC_NAME;
    }

    // 下发文件 1
    //qDebug() << "\n************************************************************************************************************************";
    //qDebug() << "********** sendFile " + QDateTime::currentDateTime().toString("进： yyyyMMdd hh:mm:ss.zzz");
    int res = m_traffic->sendFile((m_illegalPicPath + ILLEGAL_PIC_NAME).toLocal8Bit(),
                                  QString(ILLEGAL_PIC_NAME).toLocal8Bit());
    //qDebug() << "********** sendFile " + QDateTime::currentDateTime().toString("出： yyyyMMdd hh:mm:ss.zzz");
    //qDebug() << "********************************************************************************v****************************************\n";

    // 发送节目
    char* program = QString(PROGRAM2).arg(ILLEGAL_PIC_NAME).toLocal8Bit().data();
    //qDebug() << "\n************************************************************************************************************************";
    //qDebug() << "********** sendPlayList " + QDateTime::currentDateTime().toString("进： yyyyMMdd hh:mm:ss.zzz");
    res = m_traffic->sendPlayList(1, program);
    //qDebug() << "********** sendPlayList " + QDateTime::currentDateTime().toString("出： yyyyMMdd hh:mm:ss.zzz");
    //qDebug() << "************************************************************************************************************************\n";
    m_playFlag = 0;
    m_Back2DefaultProgramTimeFlag = 0;
}

void NovaControllerWorker::slotPlayProgram3(int fontSize, QString content, int audioTimes, QString voiceContent
                                            , int audioSwitch, int audiovolume , QString base64)
{
    QImage image;
    image.loadFromData(QByteArray::fromBase64(base64.toLocal8Bit()));

    // 保存图片
    if(!base64.isEmpty()){
        image.save(m_illegalPicPath + ILLEGAL_PIC_NAME, "jpg", m_imgSaveLevel);
        qDebug() << m_illegalPicPath + ILLEGAL_PIC_NAME;
    }

    // 下发文件 1
    // qDebug() << "\n************************************************************************************************************************";
    // qDebug() << "************************************************ sendFile " + QDateTime::currentDateTime().toString("进： yyyyMMdd hh:mm:ss.zzz");
    int res = m_traffic->sendFile((m_illegalPicPath + ILLEGAL_PIC_NAME).toLocal8Bit(),
                                  QString(ILLEGAL_PIC_NAME).toLocal8Bit());
    //qDebug() << "********** sendFile " + QDateTime::currentDateTime().toString("出： yyyyMMdd hh:mm:ss.zzz");
    //qDebug() << "************************************************************************************************************************\n";

    // 发送节目
    // char* program = QString(PROGRAM3)
    //                     .arg(fontSize)
    //                     .arg(audioTimes)
    //                     .arg(content)
    //                     .arg(audioSwitch)
    //                     .arg(audiovolume)
    //                     .arg(ILLEGAL_PIC_NAME).toLocal8Bit().data();
    char* program = QString(PROGRAM3)
                        .arg(fontSize)
                        .arg(content)
                        .arg(audioTimes)
                        .arg(voiceContent)
                        .arg(audioSwitch)
                        .arg(audiovolume)
                        .arg(ILLEGAL_PIC_NAME).toLocal8Bit().data();
    qDebug() << program;

    //qDebug() << "\n************************************************************************************************************************";
    //qDebug() << "********** sendPlayList " + QDateTime::currentDateTime().toString("进： yyyyMMdd hh:mm:ss.zzz");
    res = m_traffic->sendPlayList(1, program);
    qDebug() << "************************************************ sendPlayList " + QDateTime::currentDateTime().toString("出： yyyyMMdd hh:mm:ss.zzz");
    qDebug() << "************************************************************************************************************************\n";

    m_playFlag = 0;
    m_Back2DefaultProgramTimeFlag = 0;
}

void NovaControllerWorker::slotSetDefaultTxt(QString content, int size)
{
    m_defaultTxt = content;
    m_defaultTxtSize = size;
}

void NovaControllerWorker::slotSetDefaultPic(QString base64)
{
    QImage image;
    image.loadFromData(QByteArray::fromBase64(base64.toLocal8Bit()));

    // 保存图片
    if(!base64.isEmpty()){
        image.save(m_illegalPicPath + DEFAULT_PIC_NAME, "png", m_imgSaveLevel);
        qDebug() << m_illegalPicPath + DEFAULT_PIC_NAME;
    }

    m_traffic->sendFile((m_illegalPicPath + DEFAULT_PIC_NAME).toLocal8Bit(),
                        QString(DEFAULT_PIC_NAME).toLocal8Bit());

}

void NovaControllerWorker::slotSetCurrentDefaultProgram(int currentProgram)
{
    if(currentProgram > 0 && currentProgram < 4){
        m_currentDef = currentProgram;
    }else{
        m_currentDef = 3;
    }
    PlayProgramDefault();
}
