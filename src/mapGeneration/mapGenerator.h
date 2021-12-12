#pragma once

#include "globals.h"

namespace mapGenerator {
  /* mapGenerationType defines which function will be used to gneerate the map
   * 0: beta flat ground for near indefinite range
  */
  // Return value 0 pass. Anything else is a fail
  int mapGeneratorSwitch(const unsigned short &mapGenerationType, const int &seed);

  // This is the 0 generator, flat ground, near indefinite range
  int mapGen_0_betaFlat(const int &seed);

  // Test code to ensure map gen has no coordinate hiccups
  int testMapGenCoordinates();
}
