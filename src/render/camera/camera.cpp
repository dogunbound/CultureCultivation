#include "camera.h"
#include "utils/clock.h"

namespace camera {
  // used to update the camera whether it be a player camera or the map camera or etc...
  int updateCamera() {
    // Set viewMove to zero when before anything is done so that when nothing is done, it is at zero
    render::viewMove->x=0;
    render::viewMove->y=0;
    switch(cameraType) {
      case 0:
        mapCamera();
        break;
      case 1:
        break;
      default:
        std::cout << "camera type not defined.\n";
        return 1; // Undefined camera type
        break;
    }

    return 0; // Pass
  }

  // used to update the map scrolling with WASD or arrow keys
  int mapCamera() {
    // Ensures that the mapCamera doesn't move more than once every 60th of a second
    if (std::abs(utils::ctimeToMilliseconds(previousViewChangeTS - std::clock())) < 16.66666666) { // Maybe overkill to use floating point.
      return 1; // Shouldn't do anything
    }

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
    return 0; // Did something
  }
}
