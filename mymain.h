#ifndef MYMAIN_H
#define MYMAIN_H

#include <QObject>

class MyHttpServer;

class MyMain : public QObject
{
    Q_OBJECT
public:
    explicit MyMain(QObject *parent = nullptr);

private:
    void initMyHttpServer();

signals:

private:
    MyHttpServer* myHttpServer;
    int port;
};

#endif // MYMAIN_H
