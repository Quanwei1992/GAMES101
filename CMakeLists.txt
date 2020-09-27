cmake_minimum_required(VERSION 3.12)
include(cmake/ucm.cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_HOME_DIRECTORY}/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_CXX_STANDARD 17)

project(GAMES101)
ucm_set_runtime(STATIC)
set(CMAKE_INSTALL_PREFIX ${CMAKE_HOME_DIRECTORY})


set(TARGET_TRIPLET "x86-windows-static")
if( CMAKE_CL_64 )
  set( TARGET_TRIPLET "x64-windows-static")
endif()

set( OpenCV_DIR  ${CMAKE_HOME_DIRECTORY}/vcpkg/installed/${TARGET_TRIPLET}/share/opencv)
set( Eigen3_DIR  ${CMAKE_HOME_DIRECTORY}/vcpkg/installed/${TARGET_TRIPLET}/share/eigen3)

add_subdirectory(00)
add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(04)
add_subdirectory(05)
add_subdirectory(06)
add_subdirectory(07)



install(TARGETS 00 01 02 03 04 05 06 07 DESTINATION  output)
install(DIRECTORY 03/models DESTINATION output)
install(DIRECTORY 06/models DESTINATION output)
install(DIRECTORY 07/models DESTINATION output)