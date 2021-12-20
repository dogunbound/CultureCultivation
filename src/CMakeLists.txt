cmake_minimum_required(VERSION 3.22.0)

project(Culture_Cultivation VERSION 0.1)

find_package(SFML 2.5.1 COMPONENTS graphics window audio system REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")

# Tell the compiler where the source code is, and add it to the executable
set(headers 
  "globals.h"
  "assets.h"

  # ************************************ Render
  "render/render.h"

  "render/camera/camera.h"
  # ************************************ Map Generation
  "mapGeneration/mapGenerator.h"

  # ************************************ utils
  "utils/clock.h"
  "utils/assetClasses.h"
	)

set(cpp
	"main.cpp"

  # ************************************ Render
  "render/render.cpp"

  "render/camera/camera.cpp"
  # ************************************ Map Generation
  "mapGeneration/mapGenerator.cpp"
  
  # ************************************ utils
  "utils/clock.cpp"
  "utils/assetClasses.cpp"
	)

add_executable(${PROJECT_NAME} ${headers} ${cpp})

# Add the following SFML module to the application:
target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-window)
target_link_libraries(${PROJECT_NAME} sfml-system)
target_link_libraries(${PROJECT_NAME} sfml-audio)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
