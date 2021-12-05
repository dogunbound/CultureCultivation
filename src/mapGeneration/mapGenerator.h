#pragma once

#include "globals.h"

namespace mapGenerator {
  /* mapGenerationType defines which function will be used to gneerate the map
   * 0: beta flat ground for near indefinite range
  */
  // Return value 0 pass. Anything else is a fail
  int mapGeneratorSwitch(const unsigned char &mapGenerationType, const int &seed);

  // This is the 0 generator, flat ground, near indefinite range
  int mapGen_0_betaFlat(const int &seed);
}
