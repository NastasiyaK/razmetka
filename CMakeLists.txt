cmake_minimum_required(VERSION 2.8.11)
project(razmetka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -O2 -fPIC")

include_directories(${PROJECT_SOURCE_DIR}/include)

FILE(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c*)

add_executable(razmetka ${SOURCE_FILES})
