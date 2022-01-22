#include "sceneeditor.h"

#include "particleboxtool.h"

SceneEditor::SceneEditor(QWidget* parent)
  : QWidget{ parent }
{
  m_toolBarSeparator.setFrameShape(QFrame::HLine);
  m_toolBarSeparator.setFrameShadow(QFrame::Sunken);

  m_layout.addWidget(&m_toolBar);
  m_layout.addWidget(&m_toolBarSeparator);
  m_layout.addWidget(&m_sceneView);

  m_toolGroup.addAction(m_particleBoxAction);
  m_toolGroup.addAction(m_lineAction);

  m_pauseAction->setEnabled(false);
  m_stopAction->setEnabled(false);

  const int targetFps = 30;
  m_simulationStepTimer.setInterval(0);
  m_simulationViewTimer.setInterval(1000 / targetFps);

  connect(&m_simulationStepTimer, &QTimer::timeout, [this]() { m_simulation->step(1e-2, 1, 1, 10); });

  connect(&m_simulationViewTimer, &QTimer::timeout, [this]() { m_sceneView.update(); });

  connect(m_playAction, &QAction::triggered, [this]() {
    m_simulation.reset(new Simulation(m_sceneHistory.getCurrent()));
    m_stopAction->setEnabled(true);
    m_pauseAction->setEnabled(true);
    m_playAction->setEnabled(false);
    m_sceneView.setSimulation(m_simulation);
    m_simulationStepTimer.start();
    m_simulationViewTimer.start();
  });

  connect(m_stopAction, &QAction::triggered, [this]() {
    m_simulation.reset();
    m_stopAction->setEnabled(false);
    m_pauseAction->setEnabled(false);
    m_playAction->setEnabled(true);
    m_sceneView.removeSimulation();
    m_simulationStepTimer.stop();
    m_simulationViewTimer.stop();
  });

  connect(m_particleBoxAction, &QAction::triggered, [this]() {
    setSceneTool(std::shared_ptr<SceneTool>(new ParticleBoxTool(&m_sceneHistory)));
  });

  m_particleBoxAction->setCheckable(true);
  m_lineAction->setCheckable(true);
  m_toolGroup.setExclusive(true);

  m_particleBoxAction->setChecked(true);

  setSceneTool(std::shared_ptr<SceneTool>(new ParticleBoxTool(&m_sceneHistory)));
}

void
SceneEditor::setSceneTool(const std::shared_ptr<SceneTool>& sceneTool)
{
  m_sceneView.setSceneTool(sceneTool);
}
