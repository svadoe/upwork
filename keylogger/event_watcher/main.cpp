// #include <QCoreApplication>

#include <QApplication>
#include <QDebug>
#include <QTimer>

#include "event_watcher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EventWatcher watcher;

    return a.exec();
}

