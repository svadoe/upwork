#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QString>

QT_BEGIN_NAMESPACE
class QLocalServer;
QT_END_NAMESPACE

class Server: public QObject
{
  Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

public slots:
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

#endif // SERVER_H
