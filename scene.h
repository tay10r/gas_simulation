#ifndef SCENE_H
#define SCENE_H

#include <QPointF>
#include <QRectF>
#include <QVector2D>

#include <algorithm>
#include <random>
#include <vector>

struct ParticleBox final
{
  QPointF a;

  QPointF b;

  QRectF toRectF() const { return QRectF(a, b); }

  template<typename Rng>
  QVector2D sample(Rng& rng) const
  {
    std::uniform_real_distribution<float> xDist(std::min(a.x(), b.x()), std::max(a.x(), b.x()));
    std::uniform_real_distribution<float> yDist(std::min(a.y(), b.y()), std::max(a.y(), b.y()));
    return QVector2D(xDist(rng), yDist(rng));
  }

  const float width() const noexcept { return std::max(a.x(), b.x()) - std::min(a.x(), b.x()); }

  const float height() const noexcept { return std::max(a.y(), b.y()) - std::min(a.y(), b.y()); }

  const float area() const noexcept { return width() * height(); }
};

struct Scene final
{
  std::vector<ParticleBox> particleBoxes;

  void addParticleBox(const QPointF& p) { particleBoxes.emplace_back(ParticleBox{ p, p }); }
};

#endif // SCENE_H
