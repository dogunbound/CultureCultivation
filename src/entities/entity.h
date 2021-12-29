#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>

namespace entity {
  class Entity {
    protected:
      sf::Vector2f coord;
      sf::FloatRect boundingBox;
    public:
      // ****************** Construction of objects:
      // Empty constructor
      Entity();
      // Initialize with sprite, bounding box, and coordinate
      Entity(const sf::Vector2f &coord, const sf::FloatRect &boundingBox);
      // Destructor
      ~Entity();
      // Copy constructor
      Entity(const Entity &copy);
      // Operator = override
      Entity operator=(const Entity &copy);

      // Getters and setters
      const sf::Vector2f &getCoord() { return coord; }
      const sf::FloatRect &getBoundingBox() { return boundingBox; }

      void setCoord(const sf::Vector2f &coord) { this->coord = sf::Vector2f(coord); }
      void setBoundingBox(const sf::FloatRect &boundingBox) { this->boundingBox = sf::FloatRect(boundingBox); }
  };
}
