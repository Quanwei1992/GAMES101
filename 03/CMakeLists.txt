cmake_minimum_required(VERSION 3.10)

add_executable(03 main.cpp rasterizer.hpp rasterizer.cpp global.hpp Triangle.hpp Triangle.cpp Texture.hpp Texture.cpp Shader.hpp OBJ_Loader.h)
find_package(OpenCV REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(03  ${OpenCV_LIBS}  Eigen3::Eigen)