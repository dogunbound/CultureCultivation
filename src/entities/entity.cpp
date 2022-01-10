#include "entity.h"

#include "assets.h"
#include "utils/assetClasses.h"




namespace entity {
  Entity::~Entity() {}

  Entity::Entity() : sprite(sf::Sprite(assets::spriteSheets[0]->texture)), ecb(sf::FloatRect(0,0,32,32)), ecbOffset(sf::Vector2i(0,0)) { repositionSpriteToECB(); }

  Entity::Entity(const sf::Sprite &sprite, const sf::IntRect &ecb, const sf::Vector2f &coord) : 
    sprite(sprite), 
    ecb(sf::FloatRect(
          coord.x,
          coord.y,
          ecb.width,
          ecb.height
          )), 
    ecbOffset(sf::Vector2i(-ecb.left, -ecb.top)) {
      repositionSpriteToECB();
    }

  Entity::Entity(const Entity &copy) : sprite(copy.sprite), ecb(copy.ecb), ecbOffset(copy.ecbOffset) {}
  Entity Entity::operator=(const Entity &copy) { return Entity(copy); }

  void Entity::repositionSpriteToECB() { sprite.setPosition(ecb.left + ecbOffset.x, ecb.top + ecbOffset.y); }
  bool Entity::intersects(const sf::FloatRect &ecb) { return this->ecb.intersects(ecb); }
  bool Entity::intersects(const Entity &entity) { return ecb.intersects(entity.ecb); }
  bool Entity::contains(const float &x, const float &y) { return ecb.contains(x, y); }
  bool Entity::contains(const sf::Vector2f &point) { return contains(point.x, point.y); }

  void Entity::move(const float &x, const float &y) {
    ecb.left += x;
    ecb.top += y;

    repositionSpriteToECB();
  }

  void Entity::move(const sf::Vector2f &offset) { move(offset.x, offset.y); }

  void Entity::setPosition(const float &x, const float &y) {
    ecb.left = x;
    ecb.top = y;

    repositionSpriteToECB();
  }

  void Entity::setPosition(const sf::Vector2f &pos) { setPosition(pos.x, pos.y); }

  void Entity::setSpriteAndEcb(const sf::Sprite &sprite, const sf::FloatRect ecb) {
    sf::Vector2f coord = sf::Vector2f(ecb.left, ecb.top);

    this->ecb = ecb;
    this->ecb.top = coord.x;
    this->ecb.left = coord.y;

    this->sprite = sprite;

    repositionSpriteToECB();
  }

  void Entity::setSpriteTextureRect(const sf::IntRect &textureRect) {
    sprite.setTextureRect(textureRect);
  }

  void Entity::update() {
  }
}
