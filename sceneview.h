#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QTransform>
#include <QWidget>

#include <memory>

#include "history.h"
#include "scene.h"
#include "scenetool.h"
#include "simulation.h"

class QPainter;

class SceneView : public QWidget
{
public:
  SceneView(History<Scene>* sceneHistory, QWidget* parent);

  void setSceneTool(const std::shared_ptr<SceneTool>& sceneTool);

  void setSimulation(const std::shared_ptr<Simulation>& simulation);

  void removeSimulation();

protected:
  void mousePressEvent(QMouseEvent*) override;

  void mouseMoveEvent(QMouseEvent*) override;

  void mouseReleaseEvent(QMouseEvent*) override;

  void wheelEvent(QWheelEvent*) override;

  void paintEvent(QPaintEvent*) override;

  void paintGrid(QPainter&);

  void paintScene(QPainter&);

  QTransform getViewTransform() const;

  QTransform getInverseViewTransform() const;

  QPointF sceneToWindowCoords(const QPointF& p) const;

  QPointF windowToSceneCoords(float x, float y) const;

  QPointF windowToSceneCoords(const QPointF& p) const { return windowToSceneCoords(p.x(), p.y()); }

private:
  History<Scene>* m_sceneHistory;

  std::shared_ptr<SceneTool> m_sceneTool;

  std::shared_ptr<Simulation> m_simulation;

  float m_zoom = 32;
};

#endif // SCENEVIEW_H
