#include <QCoreApplication>
#include "baseclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    baseClass base;

    return a.exec();
}
