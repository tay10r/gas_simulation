#include "scenetool.h"

#include "history.h"
#include "scene.h"

SceneTool::SceneTool(History<Scene>* history)
  : m_history(history)
{}

History<Scene>&
SceneTool::getSceneHistory()
{
  return *m_history;
}

const History<Scene>&
SceneTool::getSceneHistory() const
{
  return *m_history;
}

Scene&
SceneTool::getScene()
{
  return getSceneHistory().getCurrent();
}

const Scene&
SceneTool::getScene() const
{
  return getSceneHistory().getCurrent();
}

Scene&
SceneTool::snapshotScene()
{
  m_history->snapshot();
  return getScene();
}
