#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  const double ia = 0.1;

  std::shared_ptr<Object> hit_object = objects[hit_id];

  Eigen::Vector3d shaded_color = Eigen::Vector3d(0, 0, 0);

  // Add 1 time ambient light
  shaded_color += hit_object->material->ka * ia;

  // Find intersection point p
  Eigen::Vector3d p = ray.origin + t * ray.direction;

  // Add fudge factor
  p += std::pow(10, -9) * n;

  for (std::shared_ptr<Light> light : lights) {
    // Construct shadow ray from p pointing towards light
    Eigen::Vector3d dir_to_light;
    double max_t;
    light->direction(p, dir_to_light, max_t);
    Ray shadow_ray = {p, dir_to_light};

    Eigen::Vector3d v = -ray.direction.normalized();
    Eigen::Vector3d l = dir_to_light.normalized();
    Eigen::Vector3d h = (l + v).normalized();

    int shadow_ray_hit_id;
    double t_hit;
    Eigen::Vector3d n_hit;
    // Only consider this light if the shadow ray doesn't hit another object before the light
    if (!first_hit(shadow_ray, std::numeric_limits<long double>::epsilon(), objects, shadow_ray_hit_id, t_hit, n_hit) || t_hit > max_t) {
      // p is lit so add its light contribution

      // Specular Light
      double coefficient = std::pow(std::max(0.0, n.dot(h)), hit_object->material->phong_exponent);
      Eigen::Vector3d added_light_vector = (hit_object->material->ks.array() * light->I.array()).matrix();
      shaded_color += coefficient * added_light_vector;

      // Diffuse Light
      coefficient = std::max(0.0, n.dot(l));
      added_light_vector = (hit_object->material->kd.array() * light->I.array()).matrix();
      shaded_color += coefficient * added_light_vector;
    }
  }

  return shaded_color;
  ////////////////////////////////////////////////////////////////////////////
}
