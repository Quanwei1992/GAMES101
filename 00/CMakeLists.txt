cmake_minimum_required (VERSION 2.8.11)


add_executable (00 main.cpp)
find_package(Eigen3 REQUIRED)
target_link_libraries(00 PRIVATE Eigen3::Eigen)
