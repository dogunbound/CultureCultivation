#pragma once
#include "entities/entity.h"

#include <list>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>



namespace globals {
  extern std::clock_t startTime;
  extern unsigned short coreCount;

  // Most games render chunk by chunk. I understand why that is the case now.
  // The mapchunks point to an above, 4 directions for where the next chunk is located at.
  // Map chunk will also store all entity and locations. This is to allow for easy lookup of entity data based on location
  // The sf::Sprite array is the actual ground
  const unsigned short BlocksPerChunkAxis = 32;
  const unsigned short mapSpriteSize = 32;
  const unsigned short PixelsPerChunkAxis = BlocksPerChunkAxis * mapSpriteSize;
  const unsigned short PixelsPerChunkAxisDividedBy2 = PixelsPerChunkAxis / 2; // Slight optimization for render method
  struct MapChunk {
    MapChunk* top;
    MapChunk* left;
    MapChunk* bottom;
    MapChunk* right;
    sf::Sprite sprites[BlocksPerChunkAxis][BlocksPerChunkAxis];
    sf::Vector2i coord;

    std::list<entity::Entity*> entities;
  };

  extern MapChunk* centerChunk;

  static int init() {
    centerChunk = nullptr;
    return 0;
  }
}
