set(this 00-Transformation)

add_executable (${this} main.cpp)
target_link_libraries(${this} PRIVATE Eigen3)
