cmake_minimum_required(VERSION 3.6)
project(pong-sdl)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)

add_executable(pong-sdl main.cpp)

target_compile_features(pong-sdl PRIVATE cxx_std_17)

target_compile_options(pong-sdl PRIVATE 
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>)

target_compile_definitions(pong-sdl PRIVATE $<$<CONFIG:Debug>:DEBUG>)

target_link_libraries(pong-sdl PRIVATE SDL2::SDL2 SDL2::SDL2_ttf)