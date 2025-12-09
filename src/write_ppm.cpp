#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Create file
  std::ofstream WriteFile(filename);

  if (!WriteFile) {
    return false;
  }

  if (num_channels == 1) {
    WriteFile << "P2\n";
    WriteFile << width << " " << height << "\n";
  }
  if (num_channels == 3) {
    WriteFile << "P3\n";
    WriteFile << width << " " << height << "\n";
  }
  
  WriteFile << 255 << "\n";

  // Write the data
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int index;
      if (num_channels == 1) {
        index = i * width + j;
        WriteFile << (int) data[index] << " ";
      } else {
        index = (i * width + j) * num_channels;
        WriteFile << (int) data[index] << " " << (int) data[index + 1] << " " << (int) data[index + 2] << " ";
      }
    }
    WriteFile << "\n";
  }

  // Close the file
  WriteFile.close();

  return true;
  ////////////////////////////////////////////////////////////////////////////
}
