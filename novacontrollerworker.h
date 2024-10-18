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

    // void playProgram1();
    // void playProgram2();
    // void playProgram3();

signals:
    void showMsg(QString msg);

public slots:
    void slotInit();
    void slotIllegalAct();              // 相机违法行为
    void slotPlayProgram1(int fontSize, int audioTimes, QString content, int audioSwitch, int audiovolume);
    void slotPlayProgram2(QString base64);
    void slotPlayProgram3(int fontSize, int audioTimes, QString content, int audioSwitch, int audiovolume
                          , QString base64);

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
