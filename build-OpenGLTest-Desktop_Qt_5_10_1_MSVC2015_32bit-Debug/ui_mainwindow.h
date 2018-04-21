/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <scene.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionOpen;
    QAction *actionSingle_selection;
    QAction *actionMultiple_face_selection;
    QAction *actionSingle_figure_selection;
    QAction *actionMultiple_figure_selection;
    QWidget *centralwidget;
    Scene *openGLWidget;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSingle_selection = new QAction(MainWindow);
        actionSingle_selection->setObjectName(QStringLiteral("actionSingle_selection"));
        actionMultiple_face_selection = new QAction(MainWindow);
        actionMultiple_face_selection->setObjectName(QStringLiteral("actionMultiple_face_selection"));
        actionMultiple_face_selection->setCheckable(true);
        actionSingle_figure_selection = new QAction(MainWindow);
        actionSingle_figure_selection->setObjectName(QStringLiteral("actionSingle_figure_selection"));
        actionMultiple_figure_selection = new QAction(MainWindow);
        actionMultiple_figure_selection->setObjectName(QStringLiteral("actionMultiple_figure_selection"));
        actionMultiple_figure_selection->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        openGLWidget = new Scene(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 300, 341));
        openGLWidget->setMouseTracking(true);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_as);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QApplication::translate("MainWindow", "New scene", nullptr));
        actionSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save as", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actionSingle_selection->setText(QApplication::translate("MainWindow", "Single face selection", nullptr));
        actionMultiple_face_selection->setText(QApplication::translate("MainWindow", "Multiple face selection", nullptr));
        actionSingle_figure_selection->setText(QApplication::translate("MainWindow", "Single figure selection", nullptr));
        actionMultiple_figure_selection->setText(QApplication::translate("MainWindow", "Multiple figure selection", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
