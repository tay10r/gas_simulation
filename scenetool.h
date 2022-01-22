#ifndef SCENETOOL_H
#define SCENETOOL_H

#include <QMouseEvent>

class Scene;

template<typename T>
class History;

class SceneTool
{
public:
  SceneTool(History<Scene>* history);

  virtual ~SceneTool() = default;

  /// @return Whether or not the scene was modified.
  virtual bool mousePressEvent(const QPointF&, Qt::MouseButton) = 0;

  /// @return Whether or not the scene was modified.
  virtual bool mouseReleaseEvent(const QPointF&, Qt::MouseButton) = 0;

  /// @return Whether or not the scene was modified.
  virtual bool mouseMoveEvent(const QPointF&) = 0;

protected:
  History<Scene>& getSceneHistory();

  const History<Scene>& getSceneHistory() const;

  Scene& getScene();

  const Scene& getScene() const;

  Scene& snapshotScene();

private:
  History<Scene>* m_history;
};

#endif // SCENETOOL_H
