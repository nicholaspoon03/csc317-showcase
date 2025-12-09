#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "read_json.h"
#include "write_ppm.h"
#include "viewing_ray.h"
#include "raycolor.h"
#include <Eigen/Core>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>
#include <random>
#include "PointLight.h"


int main(int argc, char * argv[])
{
  Camera camera;
  std::vector< std::shared_ptr<Object> > objects;
  std::vector< std::shared_ptr<Light> > lights;
  // Read a camera and scene description from given .json file
  read_json(
    argc<=1?"../data/sphere-and-plane.json":argv[1],
    camera,
    objects,
    lights);

  int width =  640;
  int height = 360;

  std::uniform_int_distribution<> x(-10, 10);
  std::uniform_int_distribution<> y(-10, 10);
  std::uniform_int_distribution<> z(-10, 10);
  std::random_device rd;
  std::mt19937 gen(rd());

  for (int frames = 0; frames < 10; frames++) {
    PointLight light;
    Eigen::Vector3d position = Eigen::Vector3d(
      x(gen),
      y(gen),
      z(gen)
    );

    light.p = position;
    light.I = Eigen::Vector3d(1,1,1);
    lights.push_back(std::make_shared<PointLight>(light));

    std::vector<unsigned char> rgb_image(3*width*height);
    // For each pixel (i,j)
    for(unsigned i=0; i<height; ++i) 
    {
      for(unsigned j=0; j<width; ++j)
      {
        // Set background color
        Eigen::Vector3d rgb(0,0,0);
  
        // Compute viewing ray
        Ray ray;
        viewing_ray(camera,i,j,width,height,ray);
        
        // Shoot ray and collect color
        raycolor(ray,1.0,objects,lights,0,rgb);
  
        // Write double precision color into image
        auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
        rgb_image[0+3*(j+width*i)] = 255.0*clamp(rgb(0));
        rgb_image[1+3*(j+width*i)] = 255.0*clamp(rgb(1));
        rgb_image[2+3*(j+width*i)] = 255.0*clamp(rgb(2));
  
      }
    }
  
    write_ppm("rgb" + std::to_string(frames) + ".ppm",rgb_image,width,height,3);
  }

  system("ffmpeg -framerate 30 -i rgb%d.ppm -pix_fmt yuv420p rgb.mp4");
}
