#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d t1 = std::get<1>(this->corners) - std::get<0>(this->corners);
  Eigen::Vector3d t2 = std::get<2>(this->corners) - std::get<0>(this->corners);

  Eigen::Vector3d e = ray.origin - std::get<0>(this->corners);

  Eigen::Matrix3d original_m;
  original_m.col(0) = t1;
  original_m.col(1) = t2;
  original_m.col(2) = -ray.direction;

  double original_m_det = original_m.determinant();

  Eigen::Matrix3d m;
  m.col(0) = e;
  m.col(1) = t2;
  m.col(2) = -ray.direction;

  double alpha = m.determinant() / original_m_det;

  m.col(0) = t1;
  m.col(1) = e;

  double beta = m.determinant() / original_m_det;

  m.col(1) = t2;
  m.col(2) = e;

  double t_candidate = m.determinant() / original_m_det;

  if (!(alpha >= 0 && beta >= 0 && alpha + beta <= 1)) {
    return false;
  } else if (t_candidate < min_t) {
    return false;
  }

  t = t_candidate;
  n = t1.cross(t2).normalized();

  return true;
  ////////////////////////////////////////////////////////////////////////////
}


