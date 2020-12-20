#ifndef WRAPPER_H
#define WRAPPER_H

#include <QObject>

// class InputMonitor;

class Wrapper: public QObject
{
  Q_OBJECT
public:
    explicit Wrapper(QObject *parent = nullptr);

    ~Wrapper();
private:
    // InputMonitor* monitor;
};

#endif // WRAPPER_H
