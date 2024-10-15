#ifndef MYMAINCLASS_H
#define MYMAINCLASS_H

#include <QObject>

class NovaController;
class MyHttpServer;

class MyMainClass : public QObject
{
    Q_OBJECT
public:
    explicit MyMainClass(QObject *parent = nullptr);
    void initNovaController();
    void initMyHttpServer();

signals:

private:
    NovaController* m_NovaController;
    MyHttpServer* myHttpServer;
};

#endif // MYMAINCLASS_H
