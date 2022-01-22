#pragma once

#include <QVector2D>

#include <random>
#include <vector>

#include "scene.h"

class QPainter;
class QTransform;

struct ParticleBox;
struct Scene;

struct Simulation final
{
  std::vector<QVector2D> positionArray;

  std::vector<QVector2D> velocityArray;

  Simulation(const Scene& scene);

  void step(float time, float dispersionEnergy, float sigma, float maxForce);

  void paint(QPainter&, const QTransform&) const;
};
