#ifndef CLIENT_H
#define CLIENT_H

#include <QDataStream>
#include <QString>
#include <QLocalSocket>

QT_BEGIN_NAMESPACE
// class QString;
// class QLocalSocket;
QT_END_NAMESPACE

// class QLocalSocket;
class Client : public QObject
{
    Q_OBJECT
public:
    // explicit Client(QObject *parent = nullptr, QString server_name);
    explicit Client(QString server_name="",QObject *parent = nullptr);

protected slots:

    void connect_to_server();
    void read_input();
    void save_to_database();

    void display_error(QLocalSocket::LocalSocketError socket_error);
    void local_socket_state();

    void format_data();

signals:
    void input_read();

protected:
    QString server_name_;
    QLocalSocket* socket_;
    QDataStream in_;
    quint32 block_size_;
    QString database_location_;
    QString input_;

    void init();
};

#endif // CLIENT_H
