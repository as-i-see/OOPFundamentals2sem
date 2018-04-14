#ifndef SAVER_H
#define SAVER_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlQuery>
#include "vertex.h"
#include <vector>

namespace Ui {
class Saver;
}

class Saver : public QMainWindow
{
    Q_OBJECT

public:
    explicit Saver(QMainWindow *parent = 0);
    ~Saver();
public slots:
    void setData(std::vector<std::vector<Vertex>>);
private slots:
    bool persist();

private:
    Ui::Saver *ui;
    QSqlDatabase db;
    QSqlQuery *saveCubeVertex, *savePrismVertex;
    QString cubeTableName, prismTableName;
    std::vector<std::vector<Vertex>> data;
};

#endif // SAVER_H
