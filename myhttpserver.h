#ifndef MYHTTPSERVER_H
#define MYHTTPSERVER_H

#include <QObject>
#include <QThread>

class MyHttpServerWorker;

class MyHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyHttpServer(int port, int novaScreen, QString face2BackUrl, QString face2BoxUrl, QString Place, QObject *parent = nullptr);
    ~MyHttpServer();

    void start();       //开始线程
    void stop();        //结束线程

signals:
    void signalStart();
    void signalPlayProgram1(int fontSize, QString content, int audioTimes, QString voiceContent, int audioSwitch, int audiovolume);
    void signalPlayProgram2(QString base64);
    void signalPlayProgram3(int fontSize, QString content, int audioTimes, QString voiceContent,
                            int audioSwitch, int audiovolume , QString base64);
    void signalSetDefaultTxt(QString content, int size);    // 设置默认节目的内容
    void signalSetDefaultPic(QString base64);     // 设置默认节目的图片
    void signalSetCurrentDefaultProgram(int currentProgram);    // 设置当前默认节目的图片编号


private:
    QThread m_workerThread;
    MyHttpServerWorker* m_work = nullptr;
};

#endif // MYHTTPSERVER_H
