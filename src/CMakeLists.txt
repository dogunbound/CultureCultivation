# Ensure that this script can only be run with modern versions of CMake that
# use config files
cmake_minimum_required(VERSION 3.22.0)

# Tell CMake what our project is called
project(Culture_Cultivation VERSION 0.1)

# Find version 2.5.0 of the SFML library on this computer,
# but only use the graphics package
# If the package can't be found, terminate the script
find_package(SFML 2.5.1 COMPONENTS graphics window audio system REQUIRED)
find_package(Boost 1.76.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

# Tell the compiler where the source code is, and add it to the executable
set(includes 
	)

set(cpp
	"main.cpp"
	)

add_executable(${PROJECT_NAME} ${includes} ${cpp})

# Add the following SFML module to the application:
target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-window)
target_link_libraries(${PROJECT_NAME} sfml-system)
target_link_libraries(${PROJECT_NAME} sfml-audio)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES} )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
