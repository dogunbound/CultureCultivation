#pragma once
#include <SFML/Graphics.hpp>



namespace entity {
  class Entity { // This class's whole goal is to abstract the ECB and the sprite information together
    private:
      sf::Sprite sprite;
      sf::FloatRect ecb; // The reason I need ecb here too is for less calculations
      sf::Vector2i ecbOffset;

      void repositionSpriteToECB();
    public:
      Entity();
      virtual ~Entity();
      Entity(const sf::Sprite &sprite, const sf::IntRect &ecb, const sf::Vector2f &coord); // we can calculate ecb + coordinate this way too!
      Entity(const Entity &copy);
      Entity operator=(const Entity &copy);

      // Helper methods
      bool intersects(const sf::FloatRect &ecb);
      bool intersects(const Entity &entity);

      bool contains(const float &x, const float &y);
      bool contains(const sf::Vector2f &point);

      // Getters and setters
      void move(const float &x, const float &y);
      void move(const sf::Vector2f &offset);

      void setPosition(const float &x, const float &y);
      void setPosition(const sf::Vector2f &coord);

      void setSpriteAndEcb(const sf::Sprite &sprite, const sf::FloatRect ecb);

      void setSpriteTextureRect(const sf::IntRect &textureRect);

      const sf::Sprite &getSprite() const { return sprite; }
      const sf::Vector2f getCoord() const { return sf::Vector2f(ecb.left, ecb.top); }
      const sf::FloatRect &getEcb() const { return ecb; }
      
      virtual void update();
  };
}
