cmake_minimum_required(VERSION 2.8)
project(facial_det)
find_package(OpenCV REQUIRED)
# add_executable(facial_det srcs/facial_detection2.cpp)
# add_executable(facial_det srcs/facial_detection.cpp)
add_executable(facial_det srcs/go_on_live.cpp)
target_link_libraries(facial_det ${OpenCV_LIBS})
