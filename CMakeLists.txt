cmake_minimum_required(VERSION 3.15...3.31)

project(
  EKG-SANDBOX
  VERSION 1.0.0
  LANGUAGES CXX
)

if(EKG_DEVELOPER_MODE)
  set(EKG_DIR "../ekg-cmake-install/lib/cmake/ekg")
endif()

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

target_link_libraries(
  ekg-showcase PUBLIC
  SDL2::SDL2
  SDL2::SDL2main
  OpenGL::GL
  GLEW::GLEW
  Freetype::Freetype
  EKG::ekg
  -static-libgcc -static-libstdc++
)

target_include_directories(
  ekg-showcase PUBLIC
  ${SDL2_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  ${FREETYPE_INCLUDE_DIRS}
  ${EKG_INCLUDE_DIRS}
)
