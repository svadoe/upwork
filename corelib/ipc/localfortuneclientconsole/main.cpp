#include <QCoreApplication>

#include "client.h"



int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    // QGuiApplication::setApplicationDisplayName(Client::tr("Local Fortune Client"));
    Client client;
    // client.show();
    return app.exec();
}
