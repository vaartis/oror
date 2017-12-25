cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

project(oror)
add_executable(oror
  src/main.cpp

  src/Game.cpp
  src/Level.cpp
  src/Player.cpp
  src/Utils.cpp)
include_directories(include)

find_package(SFML 2 REQUIRED COMPONENTS audio graphics window system network)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(oror ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_definitions(-std=c++17 -g)
