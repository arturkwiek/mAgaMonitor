#include "monitormaga.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mAgaMonitor w;
    w.show();
    return a.exec();
}
