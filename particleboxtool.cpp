#include "particleboxtool.h"

#include "scene.h"

bool
ParticleBoxTool::mousePressEvent(const QPointF& p, Qt::MouseButton button)
{
  if (button == Qt::LeftButton) {

    if (m_inAddState) {
      getScene().particleBoxes.back().b = p;
    } else {
      getScene().addParticleBox(p);
    }

    m_inAddState = !m_inAddState;
  }

  return true;
}

bool
ParticleBoxTool::mouseReleaseEvent(const QPointF&, Qt::MouseButton)
{
  return false;
}

bool
ParticleBoxTool::mouseMoveEvent(const QPointF& p)
{
  if (m_inAddState) {
    getScene().particleBoxes.back().b = p;
    return true;
  } else {
    return false;
  }
}
