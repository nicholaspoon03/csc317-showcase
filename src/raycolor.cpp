#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  rgb = Eigen::Vector3d(0,0,0);

  if (num_recursive_calls == 10) {
    return false;
  }

  int hit_id;
  double first_hit_t;
  Eigen::Vector3d first_normal_n;
  if (first_hit(ray, min_t, objects, hit_id, first_hit_t, first_normal_n)) {
    Eigen::Vector3d shaded_color = blinn_phong_shading(ray, hit_id, first_hit_t, first_normal_n, objects, lights);
    rgb += shaded_color;

    Eigen::Vector3d incoming_ray = ray.origin + first_hit_t * ray.direction + std::pow(10, -9) * first_normal_n;
    Eigen::Vector3d mirror_ray_vector = reflect(ray.direction, first_normal_n);

    Ray mirror_ray = {incoming_ray, mirror_ray_vector};

    Eigen::Vector3d recursive_rgb;
    if (raycolor(mirror_ray, std::numeric_limits<long double>::epsilon(), objects, lights, num_recursive_calls + 1, recursive_rgb)) {
      rgb += (objects[hit_id]->material->km.array() * recursive_rgb.array()).matrix();
    }

    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
