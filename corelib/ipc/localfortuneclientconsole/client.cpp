#include <QtNetwork>
#include <QDebug>
#include <iostream>
#include <QTimer>
#include <QStandardPaths>
#include <QTextStream>

#include "client.h"

// Client::Client(QWidget *parent)
Client::Client(QObject *parent)
    : QObject(parent),
      // hostLineEdit(new QLineEdit("fortuneq")),
      socket(new QLocalSocket(this))
{

    keyboard_string = "\"keystrokes\":[";
    mouse_string = "\"buttonsClicks\":[";
    /* start set log file location */
    logfilelocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    keystrokes_log = logfilelocation + "/lkeystrokes.log";
    mouseclicks_log = logfilelocation + "/lmouseclicks.log";
    qDebug() << "";
    qDebug() << "log files path: " << logfilelocation;
    qDebug() << "keystrokes log file location: " << keystrokes_log;
    qDebug() << "mouse clicks log file location: " <<mouseclicks_log;

    /*
    QDir dir(logfilelocation);
    if (!dir.exists())
        dir.mkpath(logfilelocation);
    if (!dir.exists("addins"))
        dir.mkdir("addins");

    dir.cd("addins");
    logfilelocation = dir.absoluteFilePath(id + ".limod");
    if (QFile::exists(logfilelocation))
        QFile::remove(logfilelocation);
   */
   /*
    if(QFile::copy(file_passed, addin_path))
        qDebug("copied");
    else
        qDebug("not copied");
   */
    /* end set log file location */

    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_5_10);

/*     connect(hostLineEdit, &QLineEdit::textChanged, */
            /* this, &Client::enableGetFortuneButton); */
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Client::requestNewFortune);
    timer->start(1000);

    QTimer* file_save_timer = new QTimer(this);
    connect(file_save_timer, &QTimer::timeout, this, &Client::save_to_file);
    file_save_timer->start(5000);
    /* connect(getFortuneButton, &QPushButton::clicked, */
            /* this, &Client::requestNewFortune); */
    // connect(quitButton, &QPushButton::clicked, this, &Client::close);
    connect(socket, &QLocalSocket::readyRead, this, &Client::readFortune);
    connect(socket, &QLocalSocket::errorOccurred, this, &Client::displayError);

   /*  QGridLayout *mainLayout = new QGridLayout(this); */
    // mainLayout->addWidget(hostLabel, 0, 0);
    // mainLayout->addWidget(hostLineEdit, 0, 1);
    // mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
    // mainLayout->addWidget(buttonBox, 3, 0, 1, 2);
    //
    // setWindowTitle(QGuiApplication::applicationDisplayName());
    /* hostLineEdit->setFocus(); */
}

void Client::requestNewFortune()
{
    // getFortuneButton->setEnabled(false);
    blockSize = 0;
    socket->abort();
    // socket->connectToServer(hostLineEdit->text());
    socket->connectToServer("fortuneq");
    //socket->connectToServer("myeventsmonitor");
    //qDebug() << "fortune";
}

void Client::save_to_file()
{
    QFile keystrokes_file(keystrokes_log);
    QFile mouseclicks_file(mouseclicks_log);
    int size = keyboard_string.size();
    keyboard_string.remove(size-1, 1);
    keyboard_string += "]";

    if(!keystrokes_file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << QString( tr("Save data - Unable to save current data to file: %1") ).arg(keystrokes_log);
        return;
    }

    QTextStream keystrokesStream(&keystrokes_file);
    keystrokesStream << keyboard_string << "\n";
    keystrokes_file.close();
    keyboard_string = "\"keystrokes\":[";


    size = mouse_string.size();
    mouse_string.remove(size-1, 1);
    mouse_string += "]";

    if(!mouseclicks_file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << QString( tr("Save data - Unable to save current data to file: %1") ).arg(keystrokes_log);
        return;
    }

    QTextStream mouseStream(&mouseclicks_file);
    mouseStream << mouse_string << "\n";
    mouseclicks_file.close();
    mouse_string = "\"buttonClicks\":[";

}

void Client::readFortune()
{
    if (blockSize == 0) {
        // Relies on the fact that QDataStream serializes a quint32 into
        // sizeof(quint32) bytes
        if (socket->bytesAvailable() < (int)sizeof(quint32))
            return;
        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize || in.atEnd())
        return;

    QString nextFortune;
    in >> nextFortune;

    int inextFortune = nextFortune.split(" ")[0].toInt();

    int icurrentFortune = currentFortune.toInt();

    if (inextFortune == icurrentFortune) {
        inextFortune = 0;
    } else {
        inextFortune = inextFortune - icurrentFortune;
    }

    int key_count_next = nextFortune.split(" ")[1].toInt();
    int icurrentKeyCount = currentKeyCount.toInt();

    if (key_count_next == icurrentKeyCount) {
        key_count_next = 0;
    } else {
        key_count_next = key_count_next - icurrentKeyCount;
    }

    currentFortune = nextFortune.split(" ")[0];
    currentKeyCount = nextFortune.split(" ")[1];

    mouse_string += "\"" + QString::number(inextFortune) + "\",";
    keyboard_string += "\"" + QString::number(key_count_next) + "\",";
    std::cout << mouse_string.toUtf8().constBegin() << "\n";
    std::cout << keyboard_string.toUtf8().constBegin() << "\n";
}

void Client::displayError(QLocalSocket::LocalSocketError socketError)
{
    switch (socketError) {
    case QLocalSocket::ServerNotFoundError:
        qDebug() << "The host was not found. Please make sure that the server is running and that the server name is correct.";
        break;
    case QLocalSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer. Make sure the fortune server is running, and check that the server name is correct.";
        break;
    case QLocalSocket::PeerClosedError:
        break;
    default:
         qDebug() << "The following error occurred: %1.";
    }
}
