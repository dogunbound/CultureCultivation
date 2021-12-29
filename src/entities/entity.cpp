#include "entity.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace entity {
  Entity::Entity() {

  }

  Entity::Entity(const sf::Vector2f &coord, const sf::FloatRect &boundingBox) : coord (coord), boundingBox (boundingBox) {
  }

  // We have no dynamically loaded things here :)
  Entity::~Entity() {

  }

  Entity::Entity(const Entity &copy) {
    coord = copy.coord;
    boundingBox = copy.boundingBox;
  }

  Entity Entity::operator=(const Entity &copy) {
    return Entity(copy);
  }
}
