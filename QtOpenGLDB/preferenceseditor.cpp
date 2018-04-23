#include "preferenceseditor.h"
#include "ui_preferenceseditor.h"

preferencesEditor::preferencesEditor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::preferencesEditor) {
  ui->setupUi(this);
}

preferencesEditor::~preferencesEditor() { delete ui; }

void preferencesEditor::on_pushButton_clicked() {
  std::vector<float> prefs;
  float rotationAngle = ui->lineEdit->text().toFloat();
  prefs.push_back(rotationAngle);
  float translationUnit = ui->lineEdit_2->text().toFloat();
  prefs.push_back(translationUnit);
  float scalingFactor = ui->lineEdit_3->text().toFloat();
  prefs.push_back(scalingFactor);
  emit sendPrefs(prefs);
}
