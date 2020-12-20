// #include <QCoreApplication>

#include <QApplication>
#include <QDebug>
#include <QTimer>

// #include "singleton.h"
#include "mycocoaeventfilter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyCocoaEventFilter c;

    // Singleton singleton;



    return a.exec();
}


/*
// #include <QApplication>
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[]) {
// QApplication a(argc, argv);
QCoreApplication a(argc, argv);

QTimer t;
int counter;
QObject::connect(&t, &QTimer::timeout, [&](){
    //do stuff
    counter++;
    qDebug() << counter;
    // a.exit();
});
t.start(1000);

return a.exec();
}
*/

