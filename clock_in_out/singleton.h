#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>
#include <QThread>

class MyCocoaEventFilter;
class EventsProcessor;

class Singleton : public QObject
{
    Q_OBJECT
public:
    explicit Singleton(QObject *parent = nullptr);

    // int get_counter() { return events_filter.mouse_counter; }

signals:

private slots:
  void showCounter();
private:
    MyCocoaEventFilter* events_filter_;
    EventsProcessor* events_processor_;
    QThread worker_thread_;
    int counter = 0;
};

#endif // SINGLETON_H
