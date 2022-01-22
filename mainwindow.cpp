#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(&m_tabWidget);

    m_tabWidget.addTab(&m_sceneEditor, tr("Scene"));

    m_tabWidget.addTab(&m_settingsWidget, tr("Settings"));
}

MainWindow::~MainWindow()
{
}

