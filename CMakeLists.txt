cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)

project(Pong)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(main main.cpp)
add_library(my_library STATIC Paddle.cpp Ball.cpp)


target_link_libraries(main sfml-graphics sfml-audio sfml-system my_library)