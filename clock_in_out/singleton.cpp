#include<QTimer>
#include<QDebug>

#include "mycocoaeventfilter.h"
#include "eventsprocessor.h"

#include "singleton.h"

Singleton::Singleton(QObject *parent) : QObject(parent)
  // events_filter_(new MyCocoaEventFilter),
  // events_processor_(new EventsProcessor)
{
 /*  events_processor_->moveToThread(&worker_thread_); */
  // worker_thread_.start();
/*  */
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &Singleton::showCounter);
    timer->start(1000);
}

void Singleton::showCounter()
{
  counter++;
  qDebug() << counter;
}
