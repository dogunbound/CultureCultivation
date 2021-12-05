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

  int updateCamera();

  static int mapCameraScale = 4;
  int mapCamera();
}
