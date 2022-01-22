#include "sceneview.h"

#include <QPainter>
#include <QWheelEvent>

#include <algorithm>

SceneView::SceneView(History<Scene>* sceneHistory, QWidget* parent)
  : QWidget(parent)
  , m_sceneHistory(sceneHistory)
{
  setMouseTracking(true);
}

void
SceneView::setSceneTool(const std::shared_ptr<SceneTool>& sceneTool)
{
  m_sceneTool = sceneTool;
}

void
SceneView::setSimulation(const std::shared_ptr<Simulation>& simulation)
{
  m_simulation = simulation;
}

void
SceneView::removeSimulation()
{
  m_simulation.reset();
}

void
SceneView::paintEvent(QPaintEvent*)
{
  QPainter painter(this);

  if (m_simulation) {

    painter.fillRect(0, 0, width(), height(), QBrush(QColor(0, 0, 0, 0xff)));

    m_simulation->paint(painter, getViewTransform());

  } else {

    painter.fillRect(0, 0, width(), height(), QBrush(QColor(0xff, 0xff, 0xff, 0xff)));

    paintGrid(painter);

    paintScene(painter);
  }
}

void
SceneView::paintGrid(QPainter& painter)
{
  const QSize s = size();

  const int rows = s.height() / m_zoom;

  const int cols = s.width() / m_zoom;

  painter.setPen(QPen(QColor(0x00, 0x00, 0xff, 0x18)));

  for (int y = 0; y < rows; y++) {

    const qreal yLine = y * m_zoom;

    painter.drawLine(0, yLine, s.width(), yLine);
  }

  for (int x = 0; x < cols; x++) {

    const qreal xLine = x * m_zoom;

    painter.drawLine(xLine, 0, xLine, s.height());
  }
}

void
SceneView::paintScene(QPainter& painter)
{
  const Scene& scene = m_sceneHistory->getCurrent();

  for (const ParticleBox& particleBox : scene.particleBoxes) {

    const QRectF rect(sceneToWindowCoords(particleBox.a), sceneToWindowCoords(particleBox.b));

    painter.fillRect(rect, QBrush(QColor(0, 0xff, 0, 0x20)));
  }
}

namespace {

template<typename T>
T
clamp(T x, T min, T max)
{
  return std::min(max, std::max(x, min));
}

} // namespace

void
SceneView::wheelEvent(QWheelEvent* event)
{
  const float minZoom = 4.0f;
  const float maxZoom = 128.0f;

  m_zoom = clamp(m_zoom + (event->angleDelta().y() / 256.0f), minZoom, maxZoom);

  update();
}

void
SceneView::mousePressEvent(QMouseEvent* event)
{
  if (m_sceneTool) {

    m_sceneHistory->snapshot();

    const QPointF p = windowToSceneCoords(event->position());

    if (m_sceneTool->mousePressEvent(p, event->button()))
      update();
  }
}

void
SceneView::mouseReleaseEvent(QMouseEvent* event)
{
  if (m_sceneTool) {

    const QPointF p = windowToSceneCoords(event->position());

    if (m_sceneTool->mouseReleaseEvent(p, event->button()))
      update();
  }
}

void
SceneView::mouseMoveEvent(QMouseEvent* event)
{
  if (m_sceneTool) {

    const QPointF p = windowToSceneCoords(event->position());

    if (m_sceneTool->mouseMoveEvent(p))
      update();
  }
}

QTransform
SceneView::getViewTransform() const
{
  return QTransform::fromScale(m_zoom, m_zoom);
}

QTransform
SceneView::getInverseViewTransform() const
{
  return QTransform::fromScale(1.0f / m_zoom, 1.0f / m_zoom);
}

QPointF
SceneView::sceneToWindowCoords(const QPointF& p) const
{
  return getViewTransform().map(p);
}

QPointF
SceneView::windowToSceneCoords(float x, float y) const
{
  return getInverseViewTransform().map(QPointF(x, y));
}
