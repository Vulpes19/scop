cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)
project(scop)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
# find_package(SDL2_ttf CONFIG REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/ErrorHandler.cpp
    src/App.cpp
    src/Object.cpp
    src/Shader.cpp
    src/Vector.cpp
    src/Matrix.cpp
    src/TextureLoader.cpp
    src/Helpers.cpp
)

add_subdirectory(ext/glad)

add_executable(scop ${SOURCES})

target_link_libraries(scop PRIVATE 
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    # SDL2_ttf::SDL2_ttf
    glad
    opengl32
)

target_include_directories(scop PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/ext/glad/include)