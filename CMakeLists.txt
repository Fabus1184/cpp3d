cmake_minimum_required(VERSION 3.20.2)
project(cpp3d VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

message("Set project source dir: ${PROJECT_SOURCE_DIR}")

find_package(SDL2 REQUIRED)
find_package(OpenCL REQUIRED)
find_package(Threads REQUIRED)

file(GLOB SOURCES src/*.cpp)
add_executable(cpp3d ${SOURCES} ${INCLUDE})
add_compile_options(cpp3d "-g -pg")

include_directories(BEFORE include)

target_link_libraries(cpp3d ${SDL2_LIBRARIES})
target_link_libraries(cpp3d ${OpenCL_LIBRARIES})
target_link_libraries(cpp3d ${CMAKE_THREAD_LIBS_INIT})
