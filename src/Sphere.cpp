#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Solve
  // (d * d) * t^2 + 2d * (e - c) * t + (e - c) * (e - c) - r^2 = 0

  double a = ray.direction.dot(ray.direction);
  double b = (2 * ray.direction).dot(ray.origin - this->center);
  double c = (ray.origin - this->center).dot(ray.origin - this->center) - std::pow(this->radius, 2);

  double discriminant = std::pow(b, 2) - (4 * a * c);

  if (discriminant == 0) {
    double sol = (-b + sqrt(discriminant)) / (2 * a);

    if (t >= min_t) {
      t = sol;

      Eigen::Vector3d hit = ray.origin + t * ray.direction;
      n = (hit - this->center) / this->radius;
      
      return true;
    } else {
      return false;
    }
  } else if (discriminant > 0) {
    double first_sol = (-b + sqrt(discriminant)) / (2 * a);
    double sec_sol = (-b - sqrt(discriminant)) / (2 * a);

    if (first_sol >= min_t && sec_sol >= min_t) {
      if (first_sol < sec_sol) {
        t = first_sol;
      } else {
        t = sec_sol;
      }

      Eigen::Vector3d hit = ray.origin + t * ray.direction;
      n = (hit - this->center) / this->radius;

      return true;
    } else if (first_sol >= min_t || sec_sol >= min_t) {
      if (first_sol >= min_t) {
        t = first_sol;
      } else {
        t = sec_sol;
      }

      Eigen::Vector3d hit = ray.origin + t * ray.direction;
      n = (hit - this->center) / this->radius;

      return true;
    }

    return false;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

