#include "camera.h"
#include "utils/clock.h"

namespace camera {
  // used to update the camera whether it be a player camera or the map camera or etc...
  int updateCamera() {
    // Set worldViewMove to zero when before anything is done so that when nothing is done, it is at zero
    render::worldViewMove.x=0;
    render::worldViewMove.y=0;
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

    sf::Vector2f scaledScrubbing = render::worldViewSize;
    scaledScrubbing.x = scaledScrubbing.x / render::windowSize.x * mapCameraSpeed;
    scaledScrubbing.y = scaledScrubbing.y / render::windowSize.y * mapCameraSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      render::worldViewMove.x = -1 * scaledScrubbing.x;
      previousViewChangeTS = std::clock();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      render::worldViewMove.x = 1 * scaledScrubbing.x;
      previousViewChangeTS = std::clock();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      render::worldViewMove.y = -1 * scaledScrubbing.y;
      previousViewChangeTS = std::clock();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      render::worldViewMove.y = 1 * scaledScrubbing.y;
      previousViewChangeTS = std::clock();
    }
    return 0; // Did something
  }
}
