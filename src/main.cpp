#include <iostream>
#include <thread>
#include <ctime>

#include "render/render.h"
#include "globals.h"

int main() {
	if (globals::init() != 0) {
    std::cout << "Initialization of global variables have failed!!!\nExiting.";
    return -1;
  }

  globals::startTime = std::clock();
  std::thread renderThread(render::render);
  renderThread.join();
  return 0;
}
