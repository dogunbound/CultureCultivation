#pragma once
#include <ctime>

namespace utils {
  float ctimeToMilliseconds(std::clock_t t) { // This converts ctime to milliseconds as a floating point number
    return 1000.0 * t / CLOCKS_PER_SEC; 
  }
}
