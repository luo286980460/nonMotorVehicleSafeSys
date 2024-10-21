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
    void signalIllegalAct();                        // 相机违法行为
    void signalPlayProgram1(int fontSize, QString content, int audioTimes, QString voiceContent, int audioSwitch, int audiovolume);
    void signalPlayProgram2(QString base64);
    void signalPlayProgram3(int fontSize, QString content, int audioTimes, QString voiceContent,
                            int audioSwitch, int audiovolume , QString base64);


private:
    QThread m_workerThread;                         // 作线程
    NovaControllerWorker *m_work = nullptr;         // 工作类
};

#endif // NOVACONTROLLER_H
