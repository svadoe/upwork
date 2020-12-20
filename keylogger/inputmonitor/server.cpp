#include <QString>
#include <functional>
#include <iostream>
#include <QDebug>
#include <QtNetwork>

#include "server.h"

Server::Server(QObject *parent): QObject(parent)
{

  server = new QLocalServer(this);
  QString serverName("fortuneq");
  QLocalServer::removeServer(serverName);
  if (!server->listen(serverName)) {
    qDebug() << tr("Unable to start the server: %1.").arg(server->errorString());
    exit(1);
  }
    
  connect(server, &QLocalServer::newConnection, this, &Server::send_counts);

}


void Server::send_counts()
{
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_10);

  const QString &message = QString::number(this->mouseclick_counter_) + " " +
                           QString::number(this->keyboard_counter_) + " " +
                           QString::number(this->mousemove_counter_); 
  
  const QString &message2 = "mouse click: " + QString::number(this->mouseclick_counter_) + " " +
                            "keystrokes: " +  QString::number(this->keyboard_counter_) + " " +
                            "mouse move: " + QString::number(this->mousemove_counter_); 
  qDebug() << message2;

  out << quint32(message.size());
  out << message;

  QLocalSocket* clientConnection = server->nextPendingConnection();
  connect(clientConnection, &QLocalSocket::disconnected,
          clientConnection, &QLocalSocket::deleteLater);

  clientConnection->write(block);
  clientConnection->flush();
  clientConnection->disconnectFromServer();
}

