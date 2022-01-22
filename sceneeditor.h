#ifndef SCENEEDITOR_H
#define SCENEEDITOR_H

#include <QActionGroup>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

#include <memory>
#include <vector>

#include "history.h"
#include "scene.h"
#include "scenetool.h"
#include "sceneview.h"
#include "simulation.h"

class SceneEditor : public QWidget
{
  Q_OBJECT
public:
  explicit SceneEditor(QWidget* parent = nullptr);

  void undo();

  void redo();

protected:
  void snapshot();

  void setSceneTool(const std::shared_ptr<SceneTool>&);

private:
  QVBoxLayout m_layout{ this };

  QToolBar m_toolBar{ this };

  QActionGroup m_toolGroup{ &m_toolBar };

  QAction* m_playAction{ m_toolBar.addAction(tr("Play")) };

  QAction* m_pauseAction{ m_toolBar.addAction(tr("Pause")) };

  QAction* m_stopAction{ m_toolBar.addAction(tr("Stop")) };

  QAction* m_toolSeparator{ m_toolBar.addSeparator() };

  QAction* m_particleBoxAction{ m_toolBar.addAction(tr("Particle Box")) };

  QAction* m_lineAction{ m_toolBar.addAction(tr("Line Boundary")) };

  QFrame m_toolBarSeparator{ this };

  History<Scene> m_sceneHistory;

  std::shared_ptr<Simulation> m_simulation;

  SceneView m_sceneView{ &m_sceneHistory, this };

  QTimer m_simulationStepTimer{ this };

  QTimer m_simulationViewTimer{ this };
};

#endif // SCENEEDITOR_H
