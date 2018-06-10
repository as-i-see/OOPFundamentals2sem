#ifndef PREFERENCESEDITOR_H
#define PREFERENCESEDITOR_H

#include <QMainWindow>
#include <vector>
namespace Ui {
class preferencesEditor;
}

class preferencesEditor : public QMainWindow {
  Q_OBJECT

public:
  explicit preferencesEditor(QWidget *parent = 0);
  ~preferencesEditor();
signals:
  void sendPrefs(std::vector<float>);

private slots:
  void on_pushButton_clicked();

private:
  Ui::preferencesEditor *ui;
};

#endif // PREFERENCESEDITOR_H
