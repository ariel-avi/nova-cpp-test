add_library(nova_lib STATIC
        json_parser.cpp
        json_parser.h
)
target_include_directories(nova_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})