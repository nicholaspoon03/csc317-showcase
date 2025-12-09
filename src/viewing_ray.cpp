#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  double normalized_x = (j + 0.5) / width;
  double normalized_y = (height - i + 0.5) / height;

  double u_i = normalized_x * camera.width - (camera.width / 2);
  double v_j = normalized_y * camera.height - (camera.height / 2);
  
  ray.direction = u_i * camera.u + v_j * camera.v - camera.d * camera.w;
  ray.origin = camera.e;
  ////////////////////////////////////////////////////////////////////////////
}
