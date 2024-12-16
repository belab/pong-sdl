cmake_minimum_required(VERSION 3.6)
project(pong-sdl VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

add_executable(pong-sdl main.cpp)

target_compile_options(pong-sdl PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>)

target_compile_definitions(pong-sdl PRIVATE $<$<CONFIG:Debug>:DEBUG>)

target_link_libraries(pong-sdl PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)