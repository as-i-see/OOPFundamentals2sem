#include "newactionform.h"
#include "ui_newactionform.h"

NewActionForm::NewActionForm(QMainWindow *parent) :
    parent(parent),
    ui(new Ui::NewActionForm)
{
    ui->setupUi(this);
    this->cubesLabel = ui->label;
    this->prismsLabel = ui->label_2;
    this->cubeCreation = new CubeCreation(this);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this->cubeCreation, SLOT(show()));
    connect(this->cubeCreation, SIGNAL(newCubeReady(std::vector<Vertex>)), this, SLOT(newCubeReady(std::vector<Vertex>)));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(creationCompleted()));
    connect(this, SIGNAL(creationCompleted(std::pair<std::vector<std::vector<Vertex>>,int>)),
            this->parent, SLOT(loadNewScene(std::pair<std::vector<std::vector<Vertex>>,int>)));

}

NewActionForm::~NewActionForm()
{
    delete ui;
}

void NewActionForm::newCubeReady(std::vector<Vertex> vertices) {
    this->cubes.push_back(vertices);
    QString presentText = this->cubesLabel->text();
    this->cubesLabel->setText(presentText + "Cube #" + QString::number(this->cubes.size()) + "\n");
}

void NewActionForm::creationCompleted() {
    emit creationCompleted({this->cubes, 666});
    this->cubesLabel->setText("");
    this->prismsLabel->setText("");
    for (auto cube : this->cubes) {
        cube.clear();
    }
    cubes.clear();
    this->close();
}
