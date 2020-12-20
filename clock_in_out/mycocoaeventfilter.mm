#include <QString>
// #include <QTimer>
#include <chrono>
#include <thread>
#include <functional>
#include <iostream>
#include <QDebug>
#include <QtNetwork>


#include "mycocoaeventfilter.h"

#import <AppKit/AppKit.h>

// EventsProcessor::EventsProcessor(QObject *parent) : QObject(parent),
MyCocoaEventFilter::MyCocoaEventFilter(QObject *parent): QObject(parent)
{

  qDebug() << "starting event filter";

  server = new QLocalServer(this);
  QString serverName("fortuneq");
  QLocalServer::removeServer(serverName);
  if (!server->listen(serverName)) {
    qDebug() << tr("Unable to start the server: %1.").arg(server->errorString());
    exit(1);
  }
    
  connect(server, &QLocalServer::newConnection, this, &MyCocoaEventFilter::send_counts);


  id monitorKeyDown;
  id monitorLeftMouseDown;
/* 
 *     id _eventMonitor = [NSEvent addLocalMonitorForEventsMatchingMask:
 *             (NSLeftMouseDownMask | NSRightMouseDownMask | NSOtherMouseDownMask | NSKeyDownMask)
 *             handler:^(NSEvent *incomingEvent) {
 *         NSEvent *result = incomingEvent;
 *         NSWindow *targetWindowForEvent = [incomingEvent window];
 *         if ([incomingEvent type] == NSKeyDown) {
 *           qDebug() << QString::fromNSString([incomingEvent characters]);
 *         }
 *         return result;
 *     }];
 *  */


    monitorKeyDown = [NSEvent addGlobalMonitorForEventsMatchingMask:NSKeyDownMask handler:^(NSEvent *evt) {
      qDebug() << QString::fromNSString([evt characters]);
        // [self logMessageToLogView:[NSString stringWithFormat:@"Key down: %@ (key code %d)", [evt characters], [evt keyCode]]];
      keyboard_counter_++;
      qDebug() << "keyboard counter: " << keyboard_counter_;
    }];


    monitorLeftMouseDown = [NSEvent addGlobalMonitorForEventsMatchingMask:NSLeftMouseDownMask handler:^(NSEvent *evt) {
      // qDebug() << "left mouse";
      NSWindow *targetWindowForEvent = [evt window];
      NSPoint location = [NSEvent mouseLocation];
      CGPoint cglocation = [NSEvent mouseLocation]; 
      // qDebug() << "x: " << location.x << ", y: " << location.y;
      NSInteger windowNumber = [NSWindow windowNumberAtPoint:cglocation belowWindowWithWindowNumber:0];

      CGWindowID windowID = (CGWindowID)windowNumber;

      CFArrayRef array = CFArrayCreate(NULL, (const void **)&windowID, 1, NULL);
      NSArray *windowInfos = (NSArray *)CGWindowListCreateDescriptionFromArray(array);
      CFRelease(array);

      if (windowInfos.count > 0) {
          NSDictionary *windowInfo = [windowInfos objectAtIndex:0];
          // NSLog(@"Window name: %@", [windowInfo objectForKey:(NSString *)kCGWindowName]);
          // NSLog(@"Window owner: %@", [windowInfo objectForKey:(NSString *)kCGWindowOwnerName]);
      }
      [windowInfos release];
      mouse_counter_++;
      qDebug() << "click counter: " << mouse_counter_;
      // qDebug() << "keyboard counter: " << keyboard_counter_;

      // qDebug() << "";


    }];

    // QTimer* timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &MyCocoaEventFilter::increase_counter);
    // // connect(timer, &QTimer::timeout, this, &MyCocoaEventFilter::reset_counter);
    // timer->start(1000);
/*  */

/*   std::thread([this]() { */
  //   while (true) {
  //     this->increase_counter();
  //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  //   }
  // }).detach();
/*  */
}


void MyCocoaEventFilter::increase_counter()
{
  button_clicks_ += "\"";
  button_clicks_ += QString::number(this->mouse_counter_);
  button_clicks_ += "\",";
  keyboard_counter_ += 1;
  // qDebug() << button_clicks_;
  std::cout << button_clicks_.toUtf8().constData() << "\n";
  this->mouse_counter_ = 0;
}


void MyCocoaEventFilter::reset_counter()
{
  this->mouse_counter_ = 0;
  this->keyboard_counter_ = 0;
}

void MyCocoaEventFilter::send_counts()
{
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_10);
  // const QString &message = "message sent";
  const QString &message = QString::number(this->mouse_counter_) + " " +
                           QString::number(this->keyboard_counter_); 
  out << quint32(message.size());
  out << message;

  QLocalSocket* clientConnection = server->nextPendingConnection();
  connect(clientConnection, &QLocalSocket::disconnected,
          clientConnection, &QLocalSocket::deleteLater);

  clientConnection->write(block);
  clientConnection->flush();
  clientConnection->disconnectFromServer();
}

