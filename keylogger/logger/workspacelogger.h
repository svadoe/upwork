/* #ifndef CLIENT_H */
// #define CLIENT_H
//
// #include <QObject>
//
// class Client : public QObject
// {
//     Q_OBJECT
// public:
//     explicit Client(QObject *parent = nullptr);
//
// signals:
//
// };
//
// #endif // CLIENT_H
/*  */
#ifndef LOGGER_H
#define LOGGER_H

// #include <QDialog>
#include <QDataStream>
#include <QLocalSocket>
#include <QFile>

// class UsageData6Model;
#include "usagedata6model.h"

class Logger : public QObject
{
    Q_OBJECT

public:
    explicit Logger(QObject *parent = nullptr);

private slots:
    void local_socket_state();

    void requestInputEvents();
    void readInputEvents();
    void save_input_events_to_database();

    void requestWorkspaceWatcherEvents();
    void readWorkspaceWatcher();

    void displayError(QLocalSocket::LocalSocketError socketError);

private:
    QLocalSocket* input_events_socket;
    QDataStream in;
    quint32 blockSize;

    QLocalSocket* workspace_watcher_socket;
    QDataStream workspace_watcher_in;
    quint32 workspace_watcher_blockSize;

    QString currentMouseClicks;
    QString currentKeyCount;
    QString currentMouseMovementCount;

    QString buttonclicks_;
    QString keystrokes_;
    QString mousemovement_;
    QString logfilelocation;
    QFile keystrokes_file;
    QFile mouseclicks_file;

    UsageData6Model usagedata6_;

    void data_to_json(QString& data);
};

#endif // LOGGER_H
