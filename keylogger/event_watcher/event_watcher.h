#ifndef EVENTWATCHER_H
#define EVENTWATCHER_H

#include <QObject>
#include <QString>

QT_BEGIN_NAMESPACE
class QLocalServer;
QT_END_NAMESPACE

class EventWatcher : public QObject
{
  Q_OBJECT
public:
    explicit EventWatcher(QObject *parent = nullptr);

    bool checkAccessibility();

 public slots:
    // void increase_counter();
    // void reset_counter();
    void send_counts();

private:
    int mouseclick_counter_ = 0;
    int mousemove_counter_ = 0;
    int keyboard_counter_ = 0;
    QString mousemove_;
    QString button_clicks_;
    QString keystrokes_;

    int counter_;

    QLocalServer *server;
    QStringList fortunes;
};

#endif // EVENTWATCHER_H
