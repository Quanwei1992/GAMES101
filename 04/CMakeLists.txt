
find_package(OpenCV REQUIRED)
add_executable(04 main.cpp)

target_link_libraries(04  ${OpenCV_LIBS})

