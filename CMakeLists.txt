cmake_minimum_required(VERSION 3.15...3.31)
include(cmake/properties.cmake)

project(
  EKG-SANDBOX
  VERSION ${EKG_SANDBOX_VERSION}
  LANGUAGES CXX
)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(EKG REQUIRED)

message(STATUS "Building EKG sandbox")

add_executable(
  ekg-showcase
  src/ekg-showcase.cpp
  src/application.hpp
)

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

message(STATUS "EKG sandbox building done!")
