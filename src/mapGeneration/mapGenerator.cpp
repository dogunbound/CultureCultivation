#include "mapGenerator.h"
#include "assets.h"

#include <stdlib.h>

namespace mapGenerator {

  int mapGeneratorSwitch(const unsigned char &mapGenerationType, const int &seed) {
    switch(mapGenerationType) {
      case 0:
        mapGen_0_betaFlat(seed);
        break;
      default:
        std::cout << "undefined map generation type\n";
        return 1; // Undefined mapGenerationType.
    }
    return 0; // Pass
  }

  int mapGen_0_betaFlat(const int &seed) {
    srand(seed);

    return 0; // Pass
  }
}
