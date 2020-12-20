#include <QCoreApplication>

#include "event_logger.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    EventLogger client;

    return app.exec();
}
