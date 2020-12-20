#include <QString>
#include <chrono>
#include <thread>
#include <functional>
#include <iostream>
#include <stdio.h>
#include <QDebug>
#include <QtNetwork>

#include "workspace_watcher.h"
 
#import <AppKit/AppKit.h>

WorkspaceWatcher::WorkspaceWatcher(QObject *parent): QObject(parent)
{

  if (checkAccessibility()) {
    qDebug() << "Accessibility Enabled";
  }
  else {
    qDebug() << "Accessibility Disabled";
  }

  qDebug() << "starting workspace watcher";

  server = new QLocalServer(this);
  QString serverName("workspace_watcher");

  QLocalServer::removeServer(serverName);
  if (!server->listen(serverName)) {
    qDebug() << tr("Unable to start the server: %1.").arg(server->errorString());
    exit(1);
  }
    
  //connect(server, &QLocalServer::newConnection, this, &WorkspaceWatcher::send_counts);
  connect(server, &QLocalServer::newConnection, this, &WorkspaceWatcher::set_client_connection);

  //connect(this, &WorkspaceWatcher::new_notification, this, &WorkspaceWatcher::send_counts);


  // NSWorkspace
  NSArray* myObserver;
  myObserver = (NSArray*)[[[NSWorkspace sharedWorkspace] notificationCenter] addObserverForName: NSWorkspaceWillLaunchApplicationNotification
                                                                             object:nil
                                                                             queue:nil
                                                                             usingBlock:^(NSNotification* note)
                         {
                           NSLog(@"%@", note.userInfo.allValues);

                           if(note) {
                             //do your action
                           }
   //                        emit new_notification("opened a new application");
                           is_new_notification = true;
                           qDebug() << is_new_notification;
                           send_counts();

                         }

                         ];

  (NSArray*)[[[NSWorkspace sharedWorkspace] notificationCenter] addObserverForName: NSWorkspaceWillSleepNotification
                                                                object:nil
                                                                queue:nil
                                                                usingBlock:^(NSNotification* note)
            {
              NSString* s = @"System going to sleep at: ";
              NSDate* now = [NSDate date];

              printf("%s  %s", [s UTF8String], [[now description] UTF8String]);
            }
            ];

  (NSArray*)[[[NSWorkspace sharedWorkspace] notificationCenter] addObserverForName: NSWorkspaceDidWakeNotification
                                                                object:nil
                                                                queue:nil
                                                                usingBlock:^(NSNotification* note)
            {

              NSString* s = @"System woke up at: ";
              NSDate* now = [NSDate date];

              printf("%s  %s", [s UTF8String], [[now description] UTF8String]);
            }
            ];
}


//void WorkspaceWatcher::send_counts(const QString& message)
void WorkspaceWatcher::send_counts()
{
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_10);
  const QString &message = "message sent";
  qDebug() << message;
  /*   const QString &message = QString::number(this->mouse_counter_) + " " + */
                             /* QString::number(this->keyboard_counter_);  */
  out << quint32(message.size());
  out << message;

  //QLocalSocket* clientConnection = server->nextPendingConnection();
/*  connect(clientConnection, &QLocalSocket::disconnected,
          clientConnection, &QLocalSocket::deleteLater);
*/
    if(is_new_notification) {
  clientConnection->write(block);
  clientConnection->flush();
  //clientConnection->disconnectFromServer();
    is_new_notification = false;
    }
}

void WorkspaceWatcher::set_client_connection()
{
  clientConnection = server->nextPendingConnection();
  connect(clientConnection, &QLocalSocket::disconnected,
          clientConnection, &QLocalSocket::deleteLater);
}


bool WorkspaceWatcher::checkAccessibility()
{
  NSDictionary* opts = @{(__bridge id)kAXTrustedCheckOptionPrompt: @YES};
  return AXIsProcessTrustedWithOptions((__bridge CFDictionaryRef)opts);
}
