#ifndef INPUTLOGGER_H
#define INPUTLOGGER_H

// #include <QDialog>
#include <QDataStream>
#include <QLocalSocket>
#include <QFile>

// class UsageData6Model;
#include "client.h"
#include "usagedata6model.h"

class InputLogger : public Client
{
    Q_OBJECT

public:
    explicit InputLogger(QString sever_name="", QObject *parent = nullptr);

private slots:
    void save_to_database();
    void format_data();

private:
    QLocalSocket* input_events_socket;
    QDataStream in;
    quint32 blockSize;

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

#endif // INPUTLOGGER_H
