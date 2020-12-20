#ifndef MYCOCOAEVENTFILTER_H
#define MYCOCOAEVENTFILTER_H

#include <QObject>
#include <QString>

QT_BEGIN_NAMESPACE
class QLocalServer;
QT_END_NAMESPACE

class MyCocoaEventFilter : public QObject
{
  Q_OBJECT
public:
    explicit MyCocoaEventFilter(QObject *parent = nullptr);
    // MyCocoaEventFilter();

 public slots:
    void increase_counter();
    void reset_counter();
    void send_counts();
    
    // void reset_counter(int& keyboard_counter, int& mouse_counter);

private:
    int mouse_counter_ = 0;
    int keyboard_counter_ = 0;
    QString button_clicks_;
    QString keystrokes;

    int counter_;

    QLocalServer *server;
    QStringList fortunes;
    
};

#endif // MYCOCOAEVENTFILTER_H
