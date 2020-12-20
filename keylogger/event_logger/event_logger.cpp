#include <QtNetwork>
#include <QDebug>
#include <iostream>
#include <QTimer>
#include <QStandardPaths>
#include <QTextStream>
#include <QDateTime>

#include "event_logger.h"
// #include "usagedata6model.h"
 
EventLogger::EventLogger(QObject *parent)
    : QObject(parent)
    , input_events_socket(new QLocalSocket(this))
    , workspace_watcher_socket(new QLocalSocket(this))
{

    logfilelocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);


    // input events client
    in.setDevice(input_events_socket);
    in.setVersion(QDataStream::Qt_5_10);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &EventLogger::requestInputEvents);
    timer->start(1000);

    QTimer* file_save_timer = new QTimer(this);
    connect(file_save_timer, &QTimer::timeout, this, &EventLogger::save_input_events_to_database);
    file_save_timer->start(5000);

    connect(input_events_socket, &QLocalSocket::readyRead, this, &EventLogger::readInputEvents);
    connect(input_events_socket, &QLocalSocket::errorOccurred, this, &EventLogger::displayError);


    // workspace watcher client

    workspace_watcher_in.setDevice(workspace_watcher_socket);
    workspace_watcher_in.setVersion(QDataStream::Qt_5_10);

    QTimer* workspace_watcher_timer = new QTimer(this);
    //connect(workspace_watcher_timer, &QTimer::timeout, this, &EventLogger::requestWorkspaceWatcherEvents);
    connect(workspace_watcher_timer, &QTimer::timeout, this, &EventLogger::local_socket_state);
    workspace_watcher_timer->start(2000);
/*  */
    // QTimer* file_save_timer = new QTimer(this);
    // connect(file_save_timer, &QTimer::timeout, this, &EventLogger::save_input_events_to_database);
    // file_save_timer->start(5000);
/*  */

    requestWorkspaceWatcherEvents();
    connect(workspace_watcher_socket, &QLocalSocket::readyRead, this, &EventLogger::readWorkspaceWatcher);
    connect(workspace_watcher_socket, &QLocalSocket::disconnected, this, &EventLogger::requestWorkspaceWatcherEvents);
    connect(workspace_watcher_socket, &QLocalSocket::errorOccurred, this, &EventLogger::displayError);


}

void EventLogger::local_socket_state()
{
  switch(workspace_watcher_socket->state()) {
    case QLocalSocket::UnconnectedState: 
      qDebug() << "socket unconnected";
      requestWorkspaceWatcherEvents();
      break;
    case QLocalSocket::ConnectingState: 
      qDebug() << "socket connecting";
      break;
    case QLocalSocket::ConnectedState: 
      qDebug() << "socket connected";
      // requestWorkspaceWatcherEvents();
      break;
    case QLocalSocket::ClosingState: 
      qDebug() << "socket ClosingState";
      break;
    default:
      qDebug() << "socket state unknown";
      break;
  }
}


void EventLogger::requestInputEvents()
{
    blockSize = 0;
    input_events_socket->abort();
    input_events_socket->connectToServer("fortuneq");
}

void EventLogger::requestWorkspaceWatcherEvents()
{
    workspace_watcher_blockSize = 0;
    workspace_watcher_socket->abort();
    workspace_watcher_socket->connectToServer("workspace_watcher");
}

void EventLogger::save_input_events_to_database()
{
  QDateTime datetime{QDateTime::currentDateTimeUtc()};
  
  QString data; 
  data_to_json(data);
  usagedata6_.insert_data(datetime, data);

  buttonclicks_.clear();
  keystrokes_.clear();
  mousemovement_.clear();
}

void EventLogger::data_to_json(QString& data)
{
  data.append("{\"activityPerSecond\":{");

  int size;

  buttonclicks_.prepend("\"buttonClicks\":[");
  size = buttonclicks_.size();
  buttonclicks_.remove(size-1, 1); //removes the last ,
  buttonclicks_.append("]");

  keystrokes_.prepend("\"keystrokes\":[");
  size = keystrokes_.size();
  keystrokes_.remove(size-1, 1); //removes the last ,
  keystrokes_.append("]");

  mousemovement_.prepend("\"mouseMovement\":[");
  size = mousemovement_.size();
  mousemovement_.remove(size-1, 1); //removes the last ,
  mousemovement_.append("]");

  data.append(buttonclicks_);
  data.append(",");
  data.append(keystrokes_);
  data.append(",");
  data.append(mousemovement_);

  data.append("}");
}


void EventLogger::readInputEvents()
{
    if (blockSize == 0) {
        // Relies on the fact that QDataStream serializes a quint32 into
        // sizeof(quint32) bytes
        if (input_events_socket->bytesAvailable() < (int)sizeof(quint32))
            return;
        in >> blockSize;
    }

    if (input_events_socket->bytesAvailable() < blockSize || in.atEnd())
        return;

    QString nextInputEvents;
    in >> nextInputEvents;

    int mouseclick_count_next = nextInputEvents.split(" ")[0].toInt();
    int icurrentMouseClicks = currentMouseClicks.toInt();

    if (mouseclick_count_next == icurrentMouseClicks) {
      mouseclick_count_next = 0;
    } else {
      mouseclick_count_next = mouseclick_count_next - icurrentMouseClicks;
    }

    int key_count_next = nextInputEvents.split(" ")[1].toInt();
    int icurrentKeyCount = currentKeyCount.toInt();

    if (key_count_next == icurrentKeyCount) {
        key_count_next = 0;
    } else {
        key_count_next = key_count_next - icurrentKeyCount;
    }

    
    int mouse_movement_count_next = nextInputEvents.split(" ")[2].toInt();
    int icurrentMouseMovement = currentMouseMovementCount.toInt();

    if (mouse_movement_count_next == icurrentMouseMovement) {
        mouse_movement_count_next = 0;
    } else {
        mouse_movement_count_next = mouse_movement_count_next - icurrentMouseMovement;
    }

    currentMouseClicks = nextInputEvents.split(" ")[0];
    currentKeyCount = nextInputEvents.split(" ")[1];
    currentMouseMovementCount = nextInputEvents.split(" ")[2];

    buttonclicks_ += "\"" + QString::number(mouseclick_count_next) + "\",";
    keystrokes_ += "\"" + QString::number(key_count_next) + "\",";
    mousemovement_ += "\"" + QString::number(mouse_movement_count_next) + "\",";

    // std::cout << buttonclicks_.toUtf8().constBegin() << "\n";
    // std::cout << keystrokes_.toUtf8().constBegin() << "\n";
    // std::cout << mousemovement_.toUtf8().constBegin() << "\n";
/*  */
}



void EventLogger::readWorkspaceWatcher()
{
    if (workspace_watcher_blockSize == 0) {
        // Relies on the fact that QDataStream serializes a quint32 into
        // sizeof(quint32) bytes
        if (workspace_watcher_socket->bytesAvailable() < (int)sizeof(quint32))
            return;
        workspace_watcher_in >> workspace_watcher_blockSize;
    }

    if (workspace_watcher_socket->bytesAvailable() < workspace_watcher_blockSize || workspace_watcher_in.atEnd())
        return;

    QString nextInputEvents;
    workspace_watcher_in >> nextInputEvents;
    qDebug() << nextInputEvents;
    workspace_watcher_blockSize = 0;
/* 
 *     int mouseclick_count_next = nextInputEvents.split(" ")[0].toInt();
 *     int icurrentMouseClicks = currentMouseClicks.toInt();
 *
 *     if (mouseclick_count_next == icurrentMouseClicks) {
 *       mouseclick_count_next = 0;
 *     } else {
 *       mouseclick_count_next = mouseclick_count_next - icurrentMouseClicks;
 *     }
 *
 *     int key_count_next = nextInputEvents.split(" ")[1].toInt();
 *     int icurrentKeyCount = currentKeyCount.toInt();
 *
 *     if (key_count_next == icurrentKeyCount) {
 *         key_count_next = 0;
 *     } else {
 *         key_count_next = key_count_next - icurrentKeyCount;
 *     }
 *
 *
 *     int mouse_movement_count_next = nextInputEvents.split(" ")[2].toInt();
 *     int icurrentMouseMovement = currentMouseMovementCount.toInt();
 *
 *     if (mouse_movement_count_next == icurrentMouseMovement) {
 *         mouse_movement_count_next = 0;
 *     } else {
 *         mouse_movement_count_next = mouse_movement_count_next - icurrentMouseMovement;
 *     }
 *
 *     currentMouseClicks = nextInputEvents.split(" ")[0];
 *     currentKeyCount = nextInputEvents.split(" ")[1];
 *     currentMouseMovementCount = nextInputEvents.split(" ")[2];
 *
 *     buttonclicks_ += "\"" + QString::number(mouseclick_count_next) + "\",";
 *     keystrokes_ += "\"" + QString::number(key_count_next) + "\",";
 *     mousemovement_ += "\"" + QString::number(mouse_movement_count_next) + "\",";
 *
 *     std::cout << buttonclicks_.toUtf8().constBegin() << "\n";
 *     std::cout << keystrokes_.toUtf8().constBegin() << "\n";
 *     std::cout << mousemovement_.toUtf8().constBegin() << "\n";
 *  */
}



void EventLogger::displayError(QLocalSocket::LocalSocketError socketError)
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

