#include <QtNetwork>
#include <QDebug>
#include <iostream>
#include <QTimer>
#include <QStandardPaths>
#include <QTextStream>
#include <QDateTime>
// #include <QLocalSocket>

#include "client.h"
// #include "usagedata6model.h"
 
Client::Client(QString server_name, QObject *parent)
  :QObject(parent)
  ,server_name_(server_name)
  ,socket_(new QLocalSocket(this))
{
  database_location_ = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

  in_.setDevice(socket_);
  in_.setVersion(QDataStream::Qt_5_10);

  connect_to_server();
  connect(socket_, &QLocalSocket::readyRead, this, &Client::read_input);
  connect(socket_, &QLocalSocket::disconnected, this, &Client::connect_to_server);
  connect(socket_, &QLocalSocket::errorOccurred, this, &Client::display_error);

  init();

}


void Client::init()
{
}


void Client::connect_to_server()
{
    block_size_ = 0;
    socket_->abort();
    socket_->connectToServer(server_name_);
}

void Client::save_to_database()
{
}


void Client::read_input()
{
  if (block_size_ == 0) {
    // Relies on the fact that QDataStream serializes a quint32 into
    // sizeof(quint32) bytes
    if (socket_->bytesAvailable() < (int)sizeof(quint32))
        return;
    in_ >> block_size_;
  }

  if (socket_->bytesAvailable() < block_size_ || in_.atEnd())
    return;

  in_ >> input_;
  block_size_ = 0;
  // qDebug() << input_;

  emit input_read();
}


void Client::display_error(QLocalSocket::LocalSocketError socket_error)
{
    switch (socket_error) {
    case QLocalSocket::ServerNotFoundError:
        qDebug() << "The host was not found. Please make sure that the server \
                     is running and that the server name is correct.";
        break;
    case QLocalSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer. Make sure the \
                     server is running, and check that the server name is \
                     correct.";
        break;
    case QLocalSocket::PeerClosedError:
        break;
    default:
         qDebug() << "The following error occurred: %1.";
    }
}


void Client::local_socket_state()
{
  switch(socket_->state()) {
    case QLocalSocket::UnconnectedState: 
      qDebug() << "socket unconnected";
      connect_to_server();
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

void Client::format_data()
{
}
