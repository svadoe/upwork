#include <QString>
// #include <QTimer>
//#include <chrono>
//#include <thread>
#include <functional>
#include <iostream>
#include <QDebug>
#include <QtNetwork>

#include "event_watcher.h"
#import <AppKit/AppKit.h>

EventWatcher::EventWatcher(QObject *parent): QObject(parent)
{

  if (checkAccessibility()) {
    qDebug() << "Accessibility Enabled";
  }
  else {
    qDebug() << "Accessibility Disabled";
  }

  qDebug() << "starting event filter";


  server = new QLocalServer(this);
  QString serverName("fortuneq");
  QLocalServer::removeServer(serverName);
  if (!server->listen(serverName)) {
    qDebug() << tr("Unable to start the server: %1.").arg(server->errorString());
    exit(1);
  }
    
  connect(server, &QLocalServer::newConnection, this, &EventWatcher::send_counts);

  [NSEvent addGlobalMonitorForEventsMatchingMask:NSKeyDownMask handler:^(NSEvent *evt) {
    qDebug() << QString::fromNSString([evt characters]);
    keyboard_counter_++;
    qDebug() << "keyboard counter: " << keyboard_counter_;
  }];


  [NSEvent addGlobalMonitorForEventsMatchingMask:NSLeftMouseDownMask handler:^(NSEvent *evt) {
    CGPoint cglocation = [NSEvent mouseLocation];
    NSInteger windowNumber = [NSWindow windowNumberAtPoint:cglocation belowWindowWithWindowNumber:0];

    CGWindowID windowID = (CGWindowID)windowNumber;

    CFArrayRef array = CFArrayCreate(NULL, (const void **)&windowID, 1, NULL);
    NSArray *windowInfos = (NSArray *)CGWindowListCreateDescriptionFromArray(array);
    CFRelease(array);

    if (windowInfos.count > 0) {
        NSDictionary *windowInfo = [windowInfos objectAtIndex:0];
    }
    [windowInfos release];
    mouseclick_counter_++;
    qDebug() << "click counter: " << mouseclick_counter_;
  }];
  

  [NSEvent addGlobalMonitorForEventsMatchingMask:NSMouseMovedMask handler:^(NSEvent *evt) {
    CGPoint cglocation = [NSEvent mouseLocation];

    NSInteger windowNumber = [NSWindow windowNumberAtPoint:cglocation belowWindowWithWindowNumber:0];

    CGWindowID windowID = (CGWindowID)windowNumber;

    CFArrayRef array = CFArrayCreate(NULL, (const void **)&windowID, 1, NULL);
    NSArray *windowInfos = (NSArray *)CGWindowListCreateDescriptionFromArray(array);
    CFRelease(array);

    [windowInfos release];
    mousemove_counter_++;
  }];

//    [NSTimer scheduledTimerWithTimeInterval:2.0
//        target:self
//        selector:@selector(targetMethod:)
//        userInfo:nil
//        repeats:YES];
}


void EventWatcher::send_counts()
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

bool EventWatcher::checkAccessibility()
{
  NSDictionary* opts = @{(__bridge id)kAXTrustedCheckOptionPrompt: @YES};
  return AXIsProcessTrustedWithOptions((__bridge CFDictionaryRef)opts);
}
