#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  t = -1;
  
  for (size_t i = 0; i < objects.size(); i++) {
    const std::shared_ptr<Object> & obj_ptr = objects[i];

    double t_candidate;
    Eigen::Vector3d n_candidate;
    if (obj_ptr->intersect(ray, min_t, t_candidate, n_candidate)) {
      if (t == -1 || t_candidate < t) {
        t = t_candidate;
        n = n_candidate;
        hit_id = i;
      }
    }
  }

  if (t == -1) {
    return false;
  } else {
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}
