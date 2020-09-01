cmake_minimum_required(VERSION 3.12)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_HOME_DIRECTORY}/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_CXX_STANDARD 17)

project(GAMES101)


set(TARGET_TRIPLET "x64-windows")
if( CMAKE_CL_64 )
  set( TARGET_TRIPLET "x64-windows")
endif()

set( OpenCV_DIR  ${CMAKE_HOME_DIRECTORY}/vcpkg/installed/${TARGET_TRIPLET}/share/opencv)
set( Eigen3_DIR  ${CMAKE_HOME_DIRECTORY}/vcpkg/installed/${TARGET_TRIPLET}/share/eigen3)

add_subdirectory(00)
add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(04)