cmake_minimum_required(VERSION 3.5)

project(Lite_motion LANGUAGES C CXX)

# Set build platform (default to x86)
set(BUILD_PLATFORM "x86" CACHE STRING "Select build CPU type: x86 or arm")

# Enable export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configure compiler for ARM platform
if(BUILD_PLATFORM STREQUAL "arm")
  message(STATUS "Configuring for ARM platform")
  set(CMAKE_C_COMPILER "aarch64-linux-gnu-gcc")
  set(CMAKE_CXX_COMPILER "aarch64-linux-gnu-g++")
else()
  message(STATUS "Configuring for x86 platform")
endif()

# Set build type and C++ standard
# set(CMAKE_BUILD_TYPE Release)  # Enable Debug
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Suppress warnings
add_compile_options(-w)

# Define SDK library name
set(SDK_LIB "lite3_sdk")

# Create static library
add_library(${PROJECT_NAME} SHARED
  src/wrapped/udpsocket.cpp
  src/wrapped/udpserver.cpp
  src/wrapped/dr_timer.cpp
  src/wrapped/receiver.cpp
  src/wrapped/sender.cpp
  "src/wrapped/command.cpp"
)

# Specify include directories
target_include_directories(${PROJECT_NAME}
  PUBLIC
    include/wrapped
  PRIVATE
    include/common
    include
    lib/eigen3
)

# Specify library search path
target_link_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    stdc++
)

# Link platform-specific SDK library
if(BUILD_PLATFORM STREQUAL "arm")
  target_link_libraries(${PROJECT_NAME}
    PRIVATE
      ${CMAKE_SOURCE_DIR}/lib/libdeeprobotics_legged_sdk_aarch64.so
  )
else()
  target_link_libraries(${PROJECT_NAME}
    PRIVATE
      ${CMAKE_SOURCE_DIR}/lib/libdeeprobotics_legged_sdk_x86_64.so
  )
endif()

# A Demo Library
add_library(${PROJECT_NAME}_demo_lib STATIC
  src/motionexample.cpp
)
target_include_directories(
  ${PROJECT_NAME}_demo_lib
  PUBLIC
    include
    include/wrapped
  PRIVATE
    lib/eigen3
    stdc++
)

# Demo to test the library
add_executable(${PROJECT_NAME}_demo main.c)
  # Compile main.c as C
  # Link with Lite_motion (C++ library)
target_link_libraries(${PROJECT_NAME}_demo 
  PRIVATE 
    ${PROJECT_NAME}
    ${PROJECT_NAME}_demo_lib 
)

# Install targets
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)