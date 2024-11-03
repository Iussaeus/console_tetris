cmake_minimum_required(VERSION 3.29)
project(console_tetris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

set(src_dir ./src)

set(utility_libs buffer;random;block;utils;renderer_utils)
set(core_libs engine;renderer;input)
set(game_libs game)
set(all_libs ${game_libs} ${core_libs} ${utility_libs})

foreach (lib IN LISTS all_libs)
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
target_link_libraries(engine PUBLIC ${utility_libs})
target_link_libraries(renderer PUBLIC ${utility_libs})
target_link_libraries(input PUBLIC ${utility_libs})
target_link_libraries(game PUBLIC ${core_libs})

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE ${game_libs} ${core_libs} ${utility_libs})