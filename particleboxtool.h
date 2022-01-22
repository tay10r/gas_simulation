#pragma once

#include "scenetool.h"

class ParticleBoxTool final : public SceneTool
{
public:
  using SceneTool::SceneTool;

  bool mousePressEvent(const QPointF&, Qt::MouseButton) override;

  bool mouseReleaseEvent(const QPointF&, Qt::MouseButton) override;

  bool mouseMoveEvent(const QPointF&) override;

private:
  bool m_inAddState = false;
};
