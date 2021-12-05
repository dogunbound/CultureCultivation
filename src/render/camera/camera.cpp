#include "camera.h"
#include "utils/clock.h"

namespace camera {
  // used to update the camera whether it be a player camera or the map camera or etc...
  int updateCamera() {
    render::viewMove->x=0;
    render::viewMove->y=0;
    if (std::abs(utils::ctimeToMilliseconds(previousViewChangeTS - std::clock())) < 16.66666666) {
      return 1;
    }
    switch(cameraType) {
      case 0:
        mapCamera();
        break;
      case 1:
        break;
      default:
        std::cout << "camera type not defined.\n";
        break;
    }

    return 0;
  }

  // used to update the map scrolling with WASD or arrow keys
  int mapCamera() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      render::viewMove->x = -1 * mapCameraScale;
      previousViewChangeTS = std::clock();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      render::viewMove->x = 1 * mapCameraScale;
      previousViewChangeTS = std::clock();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      render::viewMove->y = -1 * mapCameraScale;
      previousViewChangeTS = std::clock();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      render::viewMove->y = 1 * mapCameraScale;
      previousViewChangeTS = std::clock();
    }
    return 0;
  }
}
