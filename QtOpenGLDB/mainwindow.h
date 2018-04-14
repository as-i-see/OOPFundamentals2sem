#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "newactionform.h"
#include "saver.h"
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void sceneChanged();
    void resendData(std::vector<std::vector<Vertex>>);
public slots:
    void loadNewScene(std::pair<std::vector<std::vector<Vertex>>, int>); // TODO: second argument would be prisms
private:
    Ui::MainWindow* ui;
    NewActionForm* newActionForm;
    Saver *saver;
    Scene *scene;
};

#endif // MAINWINDOW_H
