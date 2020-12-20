#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pSocketReceive(NULL)
    , m_serverName("ServerName")
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLinkServer_clicked()
{
    if(m_pSocketReceive == NULL) {
        m_pSocketReceive = new QLocalSocket(this);
        m_pSocketReceive->connectToServer(m_serverName);

        connect(m_pSocketReceive, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
    }


}

void MainWindow::OnReadyRead()
{
    if(m_pSocketReceive) {
        QDataStream tempReadDataStream(m_pSocketReceive);
        tempReadDataStream.setVersion(QDataStream::Qt_5_15);
        QString str;
        tempReadDataStream >> str;
        ui->lineEditReceiveMsg->setText(str);
    }

}

void MainWindow::on_pushButtonSendMsg_clicked()
{

}


