#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  double denominator = this->normal.dot(ray.direction);

  if (denominator == 0) {
    return false;
  }

  double numerator = (-this->normal).dot(ray.origin - this->point);

  double t_candidate = numerator / denominator;

  if (t_candidate < min_t) {
    return false;
  } else {
    t = t_candidate;
    n = this->normal.normalized();

    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}

