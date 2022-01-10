#include "trees.h"
#include "assets.h"

#include <cmath>



namespace entity {
  struct DefaultTreeData {
    assets::SpriteSheet **spriteSheet;
    sf::IntRect ecb;
  };

  static const DefaultTreeData treeDataIds[1] = {
    { &assets::spriteSheets[2], sf::IntRect(9,111,12,7) }
  };

  Tree::~Tree() {}

  Tree::Tree() : Entity(), normalSpriteSheet(*treeDataIds[0].spriteSheet), currentSpriteSheet(*treeDataIds[0].spriteSheet), lastAnimationChange(std::clock()) {  }

  Tree::Tree(const unsigned int &id, const sf::Vector2f &coord) : Entity(
      sf::Sprite((**treeDataIds[id].spriteSheet).texture),
      treeDataIds[id].ecb,
      coord), 
  lastAnimationChange(std::clock()),
  normalSpriteSheet(*treeDataIds[id].spriteSheet) {
    currentSpriteSheet = normalSpriteSheet;
    this->setSpriteTextureRect(currentSpriteSheet->getSpriteRectAtIndex(animationFrame));
  }

  Tree::Tree(const Tree &copy) : Entity(copy), normalSpriteSheet(copy.normalSpriteSheet), currentSpriteSheet(copy.currentSpriteSheet), lastAnimationChange(copy.lastAnimationChange) {}

  Tree Tree::operator=(const Tree &copy) { return Tree(copy); }

  void Tree::setSpriteSheetToNormal() {
    currentSpriteSheet = normalSpriteSheet;
  }

  void Tree::update() {
    if (abs(lastAnimationChange - std::clock()) / CLOCKS_PER_SEC > 3) {
      lastAnimationChange = std::clock();

      if (animationFrame + 1 >= currentSpriteSheet->numOfSprites()) {
        animationFrame = 0;
      } else {
        animationFrame++;
      }

      this->setSpriteTextureRect(currentSpriteSheet->getSpriteRectAtIndex(animationFrame));
    }
  }
}
