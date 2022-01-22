#include "simulation.h"

#include "scene.h"

#include <QPainter>

namespace {

template<typename Float>
constexpr Float
pow(Float x, int e)
{
  if (e == 1)
    return x;
  else if ((e % 2) == 0)
    return pow(x, e / 2) * pow(x, e / 2);
  else
    return x * pow(x, e - 1);
}

} // namespace

Simulation::Simulation(const Scene& scene)
{
  std::seed_seq seed{ 1234, 42, 3141 };

  std::mt19937 rng(seed);

  std::uniform_real_distribution<float> velDist(0.1);

  for (const ParticleBox& box : scene.particleBoxes) {

    const float density = 1;

    const int particleCount = box.area() * density;

    for (int i = 0; i < particleCount; i++) {

      positionArray.emplace_back(box.sample(rng));

      velocityArray.emplace_back(QPointF(velDist(rng), velDist(rng)));
    }
  }
}

void
Simulation::step(float time, float dispersionEnergy, float sigma, float maxForce)
{
  std::vector<QVector2D> pArray(positionArray.size());
  std::vector<QVector2D> vArray(velocityArray.size());

  const float sigma_a = pow(sigma, 12);
  const float sigma_b = pow(sigma, 6);

  const float mass = 1;

  for (size_t i = 0; i < positionArray.size(); i++) {

    QVector2D totalForce(0, 0);

    for (size_t j = 0; j < positionArray.size(); j++) {

      if (i == j)
        continue;

      const QVector2D delta = positionArray[i] - positionArray[j];

      const float distanceSquared = QVector2D::dotProduct(delta, delta);

      const float distance = std::sqrt(distanceSquared);

      const float d6 = pow(distanceSquared, 3);

      const float d12 = d6 * d6;

      const float k_a = sigma_a / (d12 * distance);

      const float k_b = sigma_b / (d6 * distance);

      const float force = std::min(48 * dispersionEnergy * (k_a - k_b), maxForce);

      const QVector2D direction = delta / distance;

      totalForce = totalForce + (force * direction);
    }

    const QVector2D accel = totalForce / mass;

    const QVector2D v = velocityArray[i] + (accel * time);

    vArray[i] = v;

    const QVector2D deltaP0 = velocityArray[i] * time;

    const QVector2D deltaP1 = 0.5f * accel * time * time;

    const QVector2D p = positionArray[i] + deltaP0 + deltaP1;

    pArray[i] = p;
  }

  positionArray = std::move(pArray);
  velocityArray = std::move(vArray);
}

void
Simulation::paint(QPainter& painter, const QTransform& transform) const
{
  painter.setPen(QColor(0xff, 0xff, 0xff, 0xff));

  std::vector<QPointF> points(positionArray.size());

  for (size_t i = 0; i < positionArray.size(); i++)
    points[i] = transform.map(QPointF(positionArray[i].x(), positionArray[i].y()));

  painter.drawPoints(points.data(), points.size());
}
