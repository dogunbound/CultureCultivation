#pragma once
#include "render/render.h"

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>


namespace camera {
  static std::clock_t previousViewChangeTS = std::clock();

  // Self explanatory
  static double cameraZoom = 1.0d;

  // this is to choose which camera rule to follow.
  // 0: map camera
  // 1: player camera
  static int cameraType = 0;

  // This is out switch case for updating the camera to the correct position.
  int updateCamera();

  static int mapCameraSpeed = 128;
  // These are the different kind of camera movement available
  int mapCamera();
}
