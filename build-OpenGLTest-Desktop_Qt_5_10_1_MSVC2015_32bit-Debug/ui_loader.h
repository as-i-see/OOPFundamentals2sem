/********************************************************************************
** Form generated from reading UI file 'loader.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADER_H
#define UI_LOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Loader
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Loader)
    {
        if (Loader->objectName().isEmpty())
            Loader->setObjectName(QStringLiteral("Loader"));
        Loader->resize(400, 271);
        centralwidget = new QWidget(Loader);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 80, 361, 41));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 20, 321, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 150, 271, 31));
        pushButton->setFont(font);
        Loader->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Loader);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 21));
        Loader->setMenuBar(menubar);
        statusbar = new QStatusBar(Loader);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Loader->setStatusBar(statusbar);

        retranslateUi(Loader);

        QMetaObject::connectSlotsByName(Loader);
    } // setupUi

    void retranslateUi(QMainWindow *Loader)
    {
        Loader->setWindowTitle(QApplication::translate("Loader", "MainWindow", nullptr));
        label->setText(QApplication::translate("Loader", "Enter the table name:", nullptr));
        pushButton->setText(QApplication::translate("Loader", "Load", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Loader: public Ui_Loader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADER_H
