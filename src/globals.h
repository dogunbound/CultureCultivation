#pragma once
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

namespace globals {
  extern std::clock_t startTime;

  // This is the AVL tree for bounding boxes. We use this for its simplicity and ease of mutex blocking
  struct EntityNode {
    EntityNode* childLeft;
    EntityNode* childRight;
    bool isLeaf;
  };

  struct EntityTree {
    EntityNode* nodes;
  };

  // This is the initial node in the tree
  extern EntityTree eTree;

  // This is a graph struct base off of nodes that build a simple LinkedList of map objects
  // The map starts at the center and branches off in 8 directions
  struct MapNode {
    MapNode* up;
    MapNode* upLeft;
    MapNode* upRight;
    MapNode* down;
    MapNode* downLeft;
    MapNode* downRight;
    MapNode* right;
    MapNode* left;
    sf::Sprite *sprite;
  };

  struct MapTree {
    MapNode* centerOfMap;
  };

  extern MapTree centerOfMap;
}
