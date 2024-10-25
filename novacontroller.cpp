#include "novacontroller.h"
#include "novacontrollerworker.h"

NovaController::NovaController(QString ip, int Back2DefaultProgram, QObject *parent)
    : QObject{parent}
{
    m_work = new NovaControllerWorker(ip, Back2DefaultProgram);
    m_work->moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::finished, m_work, &QObject::deleteLater);

    connect(m_work, &NovaControllerWorker::showMsg, this,&NovaController::showMsg);
    connect(this, &NovaController::signalInitWorker, m_work,&NovaControllerWorker::slotInit);
    connect(this, &NovaController::signalIllegalAct, m_work,&NovaControllerWorker::slotIllegalAct);
    connect(this, &NovaController::signalPlayProgram1, m_work,&NovaControllerWorker::slotPlayProgram1);
    connect(this, &NovaController::signalPlayProgram2, m_work,&NovaControllerWorker::slotPlayProgram2);
    connect(this, &NovaController::signalPlayProgram3, m_work,&NovaControllerWorker::slotPlayProgram3);
}

NovaController::~NovaController()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

void NovaController::start()
{
    m_workerThread.start();
    emit signalInitWorker();
}

void NovaController::stop()
{
    m_workerThread.quit();
    m_workerThread.wait();
}
