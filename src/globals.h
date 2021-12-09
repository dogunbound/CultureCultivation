#pragma once
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

namespace globals {
  extern std::clock_t startTime;
  extern unsigned short coreCount;

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
  extern EntityTree* eTree;

  // Most games render chunk by chunk. I understand why that is the case now.
  // The mapchunks point to an above, 8 directions for where the next chunk is located at.
  // The sf::Sprite array is the actual ground

  const unsigned short BlocksPerChunkAxis = 32;
  const unsigned short mapSpriteSize = 32;
  const unsigned short PixelsPerChunkAxis = BlocksPerChunkAxis * mapSpriteSize;
  struct MapChunk {
    MapChunk* top;
    MapChunk* left;
    MapChunk* bottom;
    MapChunk* right;
    MapChunk* bottomRight;
    MapChunk* bottomLeft;
    MapChunk* topRight;
    MapChunk* topLeft;
    sf::Sprite sprites[BlocksPerChunkAxis][BlocksPerChunkAxis];
    sf::Vector2i coord;
  };

  extern MapChunk* centerChunk;

  static int init() {
    eTree = nullptr;
    centerChunk = nullptr;
    return 0;
  }
}
