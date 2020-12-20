#include <QCoreApplication>

#include "inputlogger.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    InputLogger input_logger("fortuneq");

    return app.exec();
}
