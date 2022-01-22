#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFormLayout>
#include <QMainWindow>
#include <QTabWidget>

#include "sceneeditor.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  QTabWidget m_tabWidget{this};

  SceneEditor m_sceneEditor{&m_tabWidget};

  QWidget m_settingsWidget{&m_tabWidget};

  QFormLayout m_settingsLayout{&m_settingsWidget};
};

#endif  // MAINWINDOW_H
