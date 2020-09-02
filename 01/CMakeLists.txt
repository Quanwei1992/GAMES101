find_package(Eigen3 REQUIRED)
find_package(OpenCV  REQUIRED)

add_executable(01 main.cpp rasterizer.hpp rasterizer.cpp Triangle.hpp Triangle.cpp)
target_link_libraries(01 ${OpenCV_LIBS} Eigen3::Eigen)
