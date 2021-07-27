cmake_minimum_required(VERSION 3.19.1)

add_definitions(-std=c++1z)

project(Parser)

file(GLOB source_files "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB header_files "${PROJECT_SOURCE_DIR}/src/*.h")

add_executable(${PROJECT_NAME} ${source_files} ${header_files})

