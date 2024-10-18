#include <QApplication>
#include <QImage>
#include <QDebug>
#include <QDateTime>
#include <QDir>

#include "novacontrollerworker.h"
#include "include/Nova/NovaTraffic.h"
#include "NovaHeader.h"

#define ILLEGAL_PIC_NAME "/illegal.jpg"

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

void NovaControllerWorker::playProgram(int id)
{
    //qDebug() << "playProgram";
    if(m_traffic && m_timer){

        qDebug() << QString("播放节目 %1 ").arg(id);
        //emit showMsg(QString("播放节目 %1 ").arg(id));

        switch (id) {
        case 1:
            //playProgram1();
            break;
        case 2:
            //playProgram2();
            break;
        case 3:
            //playProgram3();
            break;
        default:
            break;
        }
        if(id != 1){
            m_Back2DefaultProgramTimeFlag = 0;
        }
        m_playFlag = 0;
    }
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
    playProgram(1);

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
                playProgram(2);
                m_Back2DefaultProgramTimeFlag++;
            }else if(m_Back2DefaultProgramTimeFlag < m_Back2DefaultProgramTime){    // 等待发送节目
                m_Back2DefaultProgramTimeFlag++;
            }
        }
    });
    //m_timer->start();
}

void NovaControllerWorker::slotIllegalAct()
{
    //qDebug() << QString("大屏违法:%1").arg(m_ip);
    if(m_traffic){
        // 播放节目2        临时
        playProgram(2);
    }
}

void NovaControllerWorker::slotPlayProgram1(int fontSize, int audioTimes,
                                            QString content, int audioSwitch, int audiovolume)
{



    char* program = QString(PROGRAM1)
                        .arg(fontSize)
                        .arg(audioTimes)
                        .arg(content)
                        .arg(audioSwitch)
                        .arg(audiovolume).toLocal8Bit().data();

    //qDebug() << "\n************************************************************************************************************************";
    //qDebug() << "********** sendPlayList " + QDateTime::currentDateTime().toString("进： yyyyMMdd hh:mm:ss.zzz");

    int res = m_traffic->sendPlayList(1, program);

    //qDebug() << "********** sendPlayList " + QDateTime::currentDateTime().toString("出： yyyyMMdd hh:mm:ss.zzz");
    //qDebug() << "************************************************************************************************************************\n";
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

}

void NovaControllerWorker::slotPlayProgram3(int fontSize, int audioTimes, QString content, int audioSwitch, int audiovolume
                                            , QString base64)
{
    QImage image;
    image.loadFromData(QByteArray::fromBase64(base64.toLocal8Bit()));

    // 保存图片
    if(!base64.isEmpty()){
        image.save(m_illegalPicPath + ILLEGAL_PIC_NAME, "jpg", m_imgSaveLevel);
        qDebug() << m_illegalPicPath + ILLEGAL_PIC_NAME;
    }

    // 下发文件 1
    qDebug() << "\n************************************************************************************************************************";
    qDebug() << "************************************************ sendFile " + QDateTime::currentDateTime().toString("进： yyyyMMdd hh:mm:ss.zzz");
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
                        .arg(audioTimes)
                        .arg(content)
                        .arg(audioSwitch)
                        .arg(audiovolume)
                        .arg(ILLEGAL_PIC_NAME).toLocal8Bit().data();
    //qDebug() << "\n************************************************************************************************************************";
    //qDebug() << "********** sendPlayList " + QDateTime::currentDateTime().toString("进： yyyyMMdd hh:mm:ss.zzz");
    res = m_traffic->sendPlayList(1, program);
    qDebug() << "************************************************ sendPlayList " + QDateTime::currentDateTime().toString("出： yyyyMMdd hh:mm:ss.zzz");
    qDebug() << "************************************************************************************************************************\n";


}
