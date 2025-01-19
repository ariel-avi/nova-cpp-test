cmake_minimum_required(VERSION 3.30)
project(nova_sky_cpp
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(resources)
add_subdirectory(src)
add_subdirectory(tests)

add_executable(pipeline src/main.cpp)
target_link_libraries(pipeline PUBLIC nova_lib)
