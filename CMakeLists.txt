cmake_minimum_required(VERSION 3.1)

project(SimplePlatformer)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(SimplePlatformer main.cpp Player.cpp Level.cpp libs/Tily.cpp libs/Colly.cpp)
target_link_libraries(SimplePlatformer sfml-graphics)