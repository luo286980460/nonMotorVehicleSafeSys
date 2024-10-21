#ifndef NOVACONTROLLERWORKER_H
#define NOVACONTROLLERWORKER_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class NovaTraffic;

class NovaControllerWorker : public QObject
{
    Q_OBJECT
public:
    explicit NovaControllerWorker(QString ip, int Back2DefaultProgram, QObject *parent = nullptr);

private:
    void playProgram(int id);           // 播放节目

    /*
 * 节目1 文字节目
 * 页面数量：1
 * 第一页内容：默认节目图片
 *  %1 字号
 *  %2 文字内容
 *  %3 语音播放次数
 *  %4 语音播放内容
 *  %5 语音是否开启 1开 0关闭
 *  %6 语音 音量 1-9
*/

signals:
    void showMsg(QString msg);

public slots:
    void slotInit();
    void slotIllegalAct();              // 相机违法行为
    void slotPlayProgram1(int fontSize, QString content, int audioTimes, QString voiceContent,
                          int audioSwitch, int audiovolume);
    void slotPlayProgram2(QString base64);
    void slotPlayProgram3(int fontSize, QString content, int audioTimes, QString voiceContent,
                          int audioSwitch, int audiovolume , QString base64);

private:
    QString m_ip;
    int m_port;
    NovaTraffic* m_traffic;
    QTimer* m_timer = nullptr;
    int m_Back2DefaultProgramTime;          // 播放默认节目的恢复时间
    int m_Back2DefaultProgramTimeFlag=0;    // m_Back2DefaultProgramTimeFlag == m_Back2DefaultProgramTimeFlag才有权限恢复默认节目
    int m_playFlag = 3;                     // m_playFlag == m_ProgramInterval时，才有权限播放
    int m_ProgramInterval = 3;
    QString m_illegalPicPath;               // 违法找片路径
    int m_imgSaveLevel = 10;
};

#endif // NOVACONTROLLERWORKER_H
