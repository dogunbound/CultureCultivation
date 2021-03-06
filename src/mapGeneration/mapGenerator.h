#pragma once

#include "globals.h"

namespace mapGenerator {
  extern unsigned int mapSize;
  /* mapGenerationType defines which function will be used to gneerate the map
   * 0: beta flat ground for near indefinite range
  */
  // Return value 0 pass. Anything else is a fail
  void mapGeneratorSwitch(const unsigned short &mapGenerationType, const int &seed);

  // This is the 0 generator, flat ground, near indefinite range
  void mapGen_0_betaFlat(const int &seed);
}
