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
#ifndef CLIENT_H
#define CLIENT_H

// #include <QDialog>
#include <QDataStream>
#include <QLocalSocket>
#include <QFile>

QT_BEGIN_NAMESPACE
// class QLabel;
class QLineEdit;
// class QPushButton;
QT_END_NAMESPACE

// class Client : public QDialog
class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);

private slots:
    void requestNewFortune();
    void readFortune();
    void displayError(QLocalSocket::LocalSocketError socketError);
    void save_to_file();
    // void enableGetFortuneButton();

private:

    // QLineEdit *hostLineEdit;
    // QPushButton *getFortuneButton;
    // QLabel *statusLabel;
/*  */
    QLocalSocket *socket;
    QDataStream in;
    quint32 blockSize;

    QString currentFortune;
    QString currentKeyCount;
    QString mouse_string;
    QString keyboard_string;
    QString logfilelocation;
    QString keystrokes_log;
    QString mouseclicks_log;
    QFile keystrokes_file;
    QFile mouseclicks_file;
};

#endif // CLIENT_H
