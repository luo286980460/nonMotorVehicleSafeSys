#include <QCoreApplication>
#include "mymainclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyMainClass myMain;

    return a.exec();
}
