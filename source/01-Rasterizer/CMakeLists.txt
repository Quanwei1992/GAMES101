set(this 01-Rasterizer)

add_executable (${this} main.cpp WindowsApp.hpp)
target_link_libraries(${this} PRIVATE Eigen3)
