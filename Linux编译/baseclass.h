#ifndef BASECLASS_H
#define BASECLASS_H

#include <QObject>

class MyHttpServerWorker;
class aPlayer;

class baseClass : public QObject
{
    Q_OBJECT
public:
    explicit baseClass(QObject *parent = nullptr);

private:
    void initMyHttpServer();

signals:

private:
    MyHttpServerWorker* m_myHttpServer = nullptr;
    aPlayer* m_aPlayer = nullptr;
};

#endif // BASECLASS_H
