#include "aplayer.h"

#include <QCoreApplication>
#include <QDebug>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QThread>

aPlayer::aPlayer(QObject *parent)
    : QObject{parent}
    , m_loopPattern(orderPlay)
    , m_playStatu(stopped)
{
    init();
}

bool aPlayer::addAudio(QString audioName, QString& error)
{
    QString path = QCoreApplication::applicationDirPath() + "/resources/" + audioName;
    QFile file(path);
    if(file.exists()){
        m_playList << path;
        error = "successful";
        if(m_playListIndex < 0){
            m_playListIndex = 0;
        }
        return true;

    }else{
        error = "file don't exists";
        return false;
    }
}

void aPlayer::clearPlayList()
{
    QString error;
    playStop(error);
    m_playList.clear();
    m_playListIndex = -1;
}

bool aPlayer::playStart(QString& error)
{
    QString error1;
    // 列表为空
    if(m_playList.size() < 1){
        error = "list is empty";
        m_playStatu = stopped;
        return false;
    }

    if(m_playStatu == playing){
        return false;
    }

    if(m_playListIndex == -1){
        m_playListIndex = 0;
    }

    // 如果文件流打开，先关闭文件流
    if(m_audioFile.isOpen()){
        playStop(error1);
        m_audioFile.close();
    }

    // 打开文件流
    m_audioFile.setFileName(m_playList.at(m_playListIndex));
    if (!m_audioFile.open(QIODevice::ReadOnly)) {
        error = "Failed to open audio file";
        playStop(error1);
        return false;
    }

    // 播放文件
    if(m_audioOutput) {
        m_audioOutput->start(&m_audioFile);
        error = "successful";
        m_playStatu = playing;
        return true;
    }else{
        error = "m_audioOutput is empty";
        playStop(error1);
        return false;
    }
}

bool aPlayer::playStop(QString& error)
{
    m_playStatu = stopped;
    if(m_audioOutput) {
        m_audioOutput->stop();
        error = "successful";
        return true;
    }else{
        error = "m_audioOutput is empty";
        return false;
    }
}

QStringList aPlayer::getPlayList()
{
    QStringList playList;
    int i=0;
    foreach(QString str, m_playList){
        playList <<  QString("%1. %2").arg(i).arg(str.split("/").last());
        i++;
    }
    return playList;
}

int aPlayer::getPlayListNumber()
{
    return m_playList.size();
}

void aPlayer::playIndex(int index, int times)
{
    m_playListIndex = index;
    m_loopTimes = times;
    setLoopPattern(singleCycle);

    QString error;
    playStop(error);
    playStart(error);
}

void aPlayer::setLoopPattern(e_loopPattern loopPattern)
{
    m_loopPattern = loopPattern;
}

QString aPlayer::getLoopPattern()
{
    QString loopPattern;
    switch (m_loopPattern) {
    case singleCycle:
        loopPattern = "单曲循环";
        break;
    case loopPlayback:
        loopPattern = "列表循环";
        break;
    case orderPlay:
        loopPattern = "顺序播放";
        break;
    default:
        break;
    }
    return loopPattern;
}

void aPlayer::setLoop(int loop)
{
    m_loopPattern = (e_loopPattern)loop;
}

void aPlayer::setVolume(int volume)
{
    m_audioOutput->setVolume(volume / 10.0);
}

void aPlayer::waitForCmd()
{
    QThread::msleep(300);
}

void aPlayer::init()
{
    m_playListIndex = -1;

    QList<QAudioDeviceInfo> list = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    for(int i=0; i<list.size(); i++){
        //qDebug() << list.at(i).deviceName();
        if(i==0){
            m_audioDeviceInfo = list.at(i);
        }
    }

    m_format.setCodec("audio/pcm");
    m_format.setSampleRate(48000);
    m_format.setSampleSize(16);
    m_format.setSampleType(QAudioFormat::SignedInt);
    m_format.setChannelCount(1);
    m_format.setByteOrder(QAudioFormat::LittleEndian);

    m_audioOutput = new QAudioOutput(m_audioDeviceInfo, m_format);
    qDebug() << " 输出设备: " << m_audioDeviceInfo.deviceName();
    connect(m_audioOutput, &QAudioOutput::stateChanged, this, [=](QAudio::State state){


//        qDebug() << " stateChanged: " << state;
//        qDebug() << " m_loopPattern: " << m_loopPattern;

        switch(state){
        case QAudio::ActiveState:       // 播放
        case QAudio::SuspendedState:    // 暂停
            break;
        case QAudio::StoppedState:      // 停止
            break;
        case QAudio::IdleState:         // 闲置

            slotPlayStop();
            switch(m_loopPattern){
            case singleCycle:       // 单曲循环

                m_currLoopTimes++;
                if(m_loopTimes < 0){
                    qDebug() << "1111111111111  m_currLoopTimes: " << m_currLoopTimes << "m_loopTimes: " << m_loopTimes;
                    m_currLoopTimes = 0;
                    slotPlayStart();

                    break;
                }else{
                    if(m_currLoopTimes < m_loopTimes){
                        qDebug() << "2222222222222  m_currLoopTimes: " << m_currLoopTimes << "m_loopTimes: " << m_loopTimes;
                        slotPlayStart();
                        break;
                    } else if(m_currLoopTimes == m_loopTimes){
                        qDebug() << "3333333333333  m_currLoopTimes: " << m_currLoopTimes << "m_loopTimes: " << m_loopTimes;
                        slotPlayStop();
                        m_loopTimes = -1;
                        m_currLoopTimes = 0;
                        m_loopPattern = m_lastLoopPattern;
                        break;
                    } else {
                        m_currLoopTimes = 0;
                        break;
                    }
                }

            case loopPlayback:      // 列表循环

                if(m_playListIndex < m_playList.size()-1){
                    m_playListIndex++;
                }else if(m_playListIndex == m_playList.size()-1){
                    m_playListIndex = 0;
                }

                slotPlayStart();
                break;
            case orderPlay:         // 顺序播放
                if(m_playListIndex == -1){
                    return;
                }
                if(m_playListIndex < m_playList.size()-1){
                    m_playListIndex++;
                    slotPlayStart();
                }
                if(m_playListIndex == m_playList.size()-1){
                    m_playListIndex = -1;
                }
                break;
            }
            break;
        case QAudio::InterruptedState:  // 中断
            slotPlayStop();
            break;
        }
    });
    m_audioOutput->setVolume(1.0);
}

void aPlayer::slotPlayStart()
{
    QString error;
    playStart(error);
}

void aPlayer::slotPlayStop()
{
    QString error;
    playStop(error);
}

void aPlayer::slotPlayIndex(int index, int times)
{
    m_lastLoopPattern = m_loopPattern;
    playIndex(index, times);
}

void aPlayer::slotClearPlayListp()
{
    clearPlayList();
}

void aPlayer::slotNormalCmd(e_cmd, QStringList args)
{

}

void aPlayer::slotListCmd(e_cmd, QStringList args)
{

}
