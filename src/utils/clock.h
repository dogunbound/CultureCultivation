#pragma once
#include <ctime>

namespace utils {
  float ctimeToMilliseconds(std::clock_t t) {
    return 1000.0 * t / CLOCKS_PER_SEC; 
  }
}
