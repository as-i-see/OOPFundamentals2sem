/********************************************************************************
** Form generated from reading UI file 'saver.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVER_H
#define UI_SAVER_H

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

class Ui_Saver
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Saver)
    {
        if (Saver->objectName().isEmpty())
            Saver->setObjectName(QStringLiteral("Saver"));
        Saver->resize(400, 271);
        centralwidget = new QWidget(Saver);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 30, 321, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 90, 361, 41));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 160, 271, 31));
        pushButton->setFont(font);
        Saver->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Saver);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 21));
        Saver->setMenuBar(menubar);
        statusbar = new QStatusBar(Saver);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Saver->setStatusBar(statusbar);

        retranslateUi(Saver);

        QMetaObject::connectSlotsByName(Saver);
    } // setupUi

    void retranslateUi(QMainWindow *Saver)
    {
        Saver->setWindowTitle(QApplication::translate("Saver", "MainWindow", nullptr));
        label->setText(QApplication::translate("Saver", "Enter the desired filename:", nullptr));
        pushButton->setText(QApplication::translate("Saver", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Saver: public Ui_Saver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVER_H
