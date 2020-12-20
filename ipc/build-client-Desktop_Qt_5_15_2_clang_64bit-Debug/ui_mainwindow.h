/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonBuildServer;
    QPushButton *pushButtonSendMsg;
    QPushButton *pushButtonNewProcess;
    QLineEdit *lineEditReceiveMsg;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButtonBuildServer = new QPushButton(centralwidget);
        pushButtonBuildServer->setObjectName(QString::fromUtf8("pushButtonBuildServer"));
        pushButtonBuildServer->setGeometry(QRect(40, 220, 113, 32));
        pushButtonSendMsg = new QPushButton(centralwidget);
        pushButtonSendMsg->setObjectName(QString::fromUtf8("pushButtonSendMsg"));
        pushButtonSendMsg->setGeometry(QRect(190, 220, 113, 32));
        pushButtonNewProcess = new QPushButton(centralwidget);
        pushButtonNewProcess->setObjectName(QString::fromUtf8("pushButtonNewProcess"));
        pushButtonNewProcess->setGeometry(QRect(330, 220, 113, 32));
        lineEditReceiveMsg = new QLineEdit(centralwidget);
        lineEditReceiveMsg->setObjectName(QString::fromUtf8("lineEditReceiveMsg"));
        lineEditReceiveMsg->setGeometry(QRect(190, 330, 261, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonBuildServer->setText(QCoreApplication::translate("MainWindow", "Build Server", nullptr));
        pushButtonSendMsg->setText(QCoreApplication::translate("MainWindow", "New Process", nullptr));
        pushButtonNewProcess->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
