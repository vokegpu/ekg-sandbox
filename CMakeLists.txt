cmake_minimum_required(VERSION 3.15...3.31)
include(cmake/properties.cmake)

project(
  EKG-SANDBOX
  VERSION 1.0.0
  LANGUAGES CXX
)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(EKG REQUIRED)

add_executable(
  ekg-showcase
  src/ekg-showcase.cpp
  src/application.hpp
)

message("${EKG_INCLUDE_DIRS}")

set_target_properties(
  ekg-showcase PROPERTIES
  CXX_STANDARD 17
)

target_compile_options(
  ekg-showcase PRIVATE
  ${PROPERTIES_COMPILE_OPTIONS}
)

target_link_libraries(
  ekg-showcase PRIVATE
  SDL2::SDL2
  SDL2::SDL2main
  OpenGL::GL
  GLEW::GLEW
  Freetype::Freetype
  EKG::ekg
  -static-libgcc -static-libstdc++
)
