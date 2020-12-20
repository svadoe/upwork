#ifndef WORKSPACEWATCHER_H
#define WORKSPACEWATCHER_H

#include <QObject>
#include <QString>

QT_BEGIN_NAMESPACE
class QLocalServer;
class QLocalSocket;
QT_END_NAMESPACE


const QString LOCAL_SERVER = "workspace_watcher";

class WorkspaceWatcher : public QObject
{
  Q_OBJECT
public:
    explicit WorkspaceWatcher(QObject *parent = nullptr);

    bool checkAccessibility();

 public slots:
    //void send_counts(const QString& notification);
    void send_counts();
    void set_client_connection();

  signals:
    void new_notification(const QString& notification);

private:
    int mouse_counter_ = 0;
    int keyboard_counter_ = 0;
    QString button_clicks_;
    QString keystrokes;
    bool is_new_notification = false;

    int counter_;

    QLocalServer *server;
    QLocalSocket* clientConnection;
    QStringList fortunes;
};

#endif // WORKSPACEWATCHER_H
