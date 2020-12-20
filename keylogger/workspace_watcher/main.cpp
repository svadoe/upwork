// #include <QCoreApplication>

#include <QApplication>
#include <QDebug>
#include <QTimer>

#include "workspace_watcher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WorkspaceWatcher watcher;

    return a.exec();
}

