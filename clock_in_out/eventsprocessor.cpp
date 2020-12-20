#include <QTimer>
#include <QDebug>
#include "eventsprocessor.h"

EventsProcessor::EventsProcessor(QObject *parent) : QObject(parent),
  keyboard_counter_(0),
  mouse_counter_(0)
{
    QTimer* timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &MyCocoaEventFilter::increase_counter);
    connect(timer, &QTimer::timeout,
            [this] { keyboard_counter_++; qDebug() << keyboard_counter_; emit this->get_and_reset_counter(keyboard_counter_, mouse_counter_);});
    timer->start(1000);

}
