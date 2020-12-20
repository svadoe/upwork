#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocalSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonLinkServer_clicked();
    void OnReadyRead();
    void on_pushButtonSendMsg_clicked();

private:
    Ui::MainWindow *ui;
    QLocalSocket* m_pSocketReceive;
    QString m_serverName;
};
#endif // MAINWINDOW_H
