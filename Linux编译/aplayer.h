#ifndef APLAYER_H
#define APLAYER_H

#include <QObject>
#include <QFile>
#include <QAudioOutput>

class aPlayer : public QObject
{
    Q_OBJECT
public:

    typedef enum {          // 循环模式
        singleCycle,        // 单曲循环
        loopPlayback,       // 列表循环
        orderPlay           // 顺序播放
    }e_loopPattern;

    typedef enum {          // 播放状态
        playing,            // 播放中
        pause,              // 暂停中
        stopped             // 停止
    }e_playStatus;

    explicit aPlayer(QObject *parent = nullptr);

    bool addAudio(QString audioName, QString& error);
    void clearPlayList();
    bool playStart(QString& error);
    bool playStop(QString& error);
    QStringList getPlayList();
    void setLoopPattern(e_loopPattern loopPattern);
    QString getLoopPattern();
    void setLoop(int loop);
    void setVolume(int volume);

private:
    void init();

signals:

public slots:
    void slotPlayStart();
    void slotPlayStop();
    void slotClearPlayListp();

private:
    QStringList m_playList;             // 播放列表
    int m_playListIndex;                // 播放列表下标
    e_loopPattern m_loopPattern;        // 循环模式
    e_playStatus m_playStatu;           // 播放状态
    QFile m_audioFile;                  // 音频输出的文件流
    QAudioDeviceInfo m_audioDeviceInfo; // 音频输出设备的信息
    QAudioFormat m_format;              // 音频输出的格式
    QAudioOutput* m_audioOutput         // 音频输出设备
        = nullptr;
};

#endif // APLAYER_H
