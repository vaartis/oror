cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

project(oror)
add_executable(oror
  src/main.cpp

  src/Game.cpp
  src/Level.cpp
  src/Player.cpp
  src/Utils.cpp
)
include_directories(include)

set(SFML_BUILD_AUDIO FALSE)
add_subdirectory(deps/sfml)
target_link_libraries(oror
  sfml-graphics
  sfml-window
  sfml-system
)

add_subdirectory(deps/chibi_bindings)
target_link_libraries(oror chibi_bindings)

set(IMGUI_ROOT ${CMAKE_SOURCE_DIR}/deps/imgui)
set(IMGUI_SFML_FIND_SFML NO)
set(SFML_ROOT ${CMAKE_SOURCE_DIR}/deps/sfml)
add_subdirectory(deps/imgui-sfml)
target_link_libraries(oror ImGui-SFML::ImGui-SFML)
