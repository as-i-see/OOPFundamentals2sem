/********************************************************************************
** Form generated from reading UI file 'newactionform.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWACTIONFORM_H
#define UI_NEWACTIONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewActionForm
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *NewActionForm)
    {
        if (NewActionForm->objectName().isEmpty())
            NewActionForm->setObjectName(QStringLiteral("NewActionForm"));
        NewActionForm->resize(600, 335);
        pushButton = new QPushButton(NewActionForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 30, 171, 61));
        QFont font;
        font.setPointSize(11);
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(NewActionForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(400, 30, 171, 61));
        pushButton_2->setFont(font);
        label = new QLabel(NewActionForm);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 100, 171, 221));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(NewActionForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(400, 100, 171, 221));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        pushButton_3 = new QPushButton(NewActionForm);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(200, 260, 201, 61));
        QFont font2;
        font2.setPointSize(16);
        pushButton_3->setFont(font2);

        retranslateUi(NewActionForm);

        QMetaObject::connectSlotsByName(NewActionForm);
    } // setupUi

    void retranslateUi(QWidget *NewActionForm)
    {
        NewActionForm->setWindowTitle(QApplication::translate("NewActionForm", "Form", nullptr));
        pushButton->setText(QApplication::translate("NewActionForm", "New Cube", nullptr));
        pushButton_2->setText(QApplication::translate("NewActionForm", "New hexagonal prism", nullptr));
        pushButton_3->setText(QApplication::translate("NewActionForm", "Build the scene", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewActionForm: public Ui_NewActionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWACTIONFORM_H
