#ifndef NOVACONTROLLER_H
#define NOVACONTROLLER_H

#include <QObject>
#include <QThread>

class NovaControllerWorker;

class NovaController : public QObject
{
    Q_OBJECT
public:
    explicit NovaController(QString ip, int Back2DefaultProgram, QObject *parent = nullptr);
    ~NovaController();

    void start();
    void stop();

signals:
    void showMsg(QString msg);
    void signalInitWorker();
    void signalPlayProgram1(int fontSize, QString content, int audioTimes, QString voiceContent, int audioSwitch, int audiovolume);
    void signalPlayProgram2(QString base64);
    void signalPlayProgram3(int fontSize, QString content, int audioTimes, QString voiceContent,
                            int audioSwitch, int audiovolume , QString base64);
    void signalSetDefaultTxt(QString content, int size);    // 设置默认节目的内容
    void signalSetDefaultPic(QString base64);     // 设置默认节目的图片
    void signalSetCurrentDefaultProgram(int currentProgram);    // 设置当前默认节目的图片编号


private:
    QThread m_workerThread;                         // 作线程
    NovaControllerWorker *m_work = nullptr;         // 工作类
};

#endif // NOVACONTROLLER_H
