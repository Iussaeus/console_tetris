cmake_minimum_required(VERSION 3.29)
project(console_tetris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --precompile")
set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)

include_directories(.)
include_directories(./src)

set(src_dir ./src)

set(utility_libs buffer;random;block;utils;renderer_utils)
set(main_libs engine;renderer;game)

foreach (lib IN LISTS utility_libs)
    add_library(${lib})

    target_sources(
            ${lib}
            PRIVATE
            ${src_dir}/${lib}.cpp
            PUBLIC
            FILE_SET CXX_MODULES FILES
            ${src_dir}/${lib}.cppm
    )
endforeach ()

foreach (lib IN LISTS main_libs)
    add_library(${lib})

    target_sources(
            ${lib}
            PRIVATE
            ${src_dir}/${lib}.cpp
            PUBLIC
            FILE_SET CXX_MODULES FILES
            ${src_dir}/${lib}.cppm
    )
endforeach ()

target_link_libraries(block PUBLIC buffer random)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -")
target_link_libraries(engine PUBLIC ${utility_libs})
target_link_libraries(renderer PUBLIC ${utility_libs})
target_link_libraries(game PUBLIC engine renderer)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE ${utility_libs} ${main_libs})