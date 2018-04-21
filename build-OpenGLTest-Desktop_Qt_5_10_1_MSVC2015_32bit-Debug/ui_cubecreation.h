/********************************************************************************
** Form generated from reading UI file 'cubecreation.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUBECREATION_H
#define UI_CUBECREATION_H

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

class Ui_CubeCreation
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CubeCreation)
    {
        if (CubeCreation->objectName().isEmpty())
            CubeCreation->setObjectName(QStringLiteral("CubeCreation"));
        CubeCreation->resize(800, 600);
        centralwidget = new QWidget(CubeCreation);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 791, 411));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/cube.jpg")));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 430, 241, 31));
        QFont font;
        font.setPointSize(12);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(190, 470, 113, 20));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(190, 500, 113, 20));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(190, 530, 113, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 470, 81, 20));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 500, 81, 21));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(60, 530, 81, 21));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(320, 430, 41, 31));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        label_6->setPalette(palette);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(370, 490, 161, 41));
        pushButton->setFont(font);
        CubeCreation->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CubeCreation);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        CubeCreation->setMenuBar(menubar);
        statusbar = new QStatusBar(CubeCreation);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CubeCreation->setStatusBar(statusbar);

        retranslateUi(CubeCreation);

        QMetaObject::connectSlotsByName(CubeCreation);
    } // setupUi

    void retranslateUi(QMainWindow *CubeCreation)
    {
        CubeCreation->setWindowTitle(QApplication::translate("CubeCreation", "MainWindow", nullptr));
        label_2->setText(QApplication::translate("CubeCreation", "Enter the coordinates of the point", nullptr));
        lineEdit->setText(QApplication::translate("CubeCreation", "0", nullptr));
        lineEdit_2->setText(QApplication::translate("CubeCreation", "0", nullptr));
        lineEdit_3->setText(QApplication::translate("CubeCreation", "0", nullptr));
        label_3->setText(QApplication::translate("CubeCreation", "X:", nullptr));
        label_4->setText(QApplication::translate("CubeCreation", "Y:", nullptr));
        label_5->setText(QApplication::translate("CubeCreation", "Z:", nullptr));
        label_6->setText(QApplication::translate("CubeCreation", "A", nullptr));
        pushButton->setText(QApplication::translate("CubeCreation", "Enter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CubeCreation: public Ui_CubeCreation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUBECREATION_H
