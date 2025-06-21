set(EXECUTABLE_OUTPUT_PATH "../bin")

if(EKG_DEVELOPER_MODE)
  set(EKG_DIR "../ekg-cmake-install/lib/cmake/ekg")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(
    PROPERTIES_COMPILE_OPTIONS
    -O0
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(
    PROPERTIES_COMPILE_OPTIONS
    -O1
  )
endif()
