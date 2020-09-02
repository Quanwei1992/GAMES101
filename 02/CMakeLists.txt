
find_package(OpenCV REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

add_executable(02 main.cpp rasterizer.hpp rasterizer.cpp global.hpp Triangle.hpp Triangle.cpp)
target_link_libraries(02  ${OpenCV_LIBS}  Eigen3::Eigen)
