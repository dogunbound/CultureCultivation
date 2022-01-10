#pragma once
#include "entities/entity.h"
#include "utils/assetClasses.h"

#include <SFML/Graphics.hpp>
#include <ctime>


namespace entity {
  class Tree : public Entity {
    private:
      assets::SpriteSheet *currentSpriteSheet;
      assets::SpriteSheet *normalSpriteSheet;
      std::clock_t lastAnimationChange;
      unsigned short animationFrame = 0;
    public:
      ~Tree();
      Tree();
      Tree(const unsigned int &id, const sf::Vector2f &coord);
      Tree(const Tree &copy);
      Tree operator=(const Tree &copy);

      void setSpriteSheetToNormal();

      void update();
  };
}
