#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>

#include "render/render.h"

namespace camera {
  static std::clock_t previousViewChangeTS = std::clock();

  // this is to choose which camera rule to follow.
  // 0: map camera
  // 1: player camera
  static int cameraType = 0;

  // This is out switch case for updating the camera to the correct position.
  int updateCamera();

  static int mapCameraScale = 4;
  // These are the different kind of camera movement available
  int mapCamera();
}
