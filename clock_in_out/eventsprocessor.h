#ifndef EVENTSPROCESSOR_H
#define EVENTSPROCESSOR_H

#include <QObject>

class EventsProcessor : public QObject
{
    Q_OBJECT
public:
    explicit EventsProcessor(QObject *parent = nullptr);

signals:
    void get_and_reset_counter(int& keyboard_counter, int& mouse_counter);

private:
    int keyboard_counter_;
    int mouse_counter_;
};

#endif // EVENTSPROCESSOR_H
