cmake_minimum_required(VERSION 2.8.11)
project(razmetka)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -02 -fPIC")

include_directories(${PROJECT_SOURCE_DIR}/include)

FILE(GLOB_RECURSE SOURCE_FILES src/*.c*)

add_executable(razmetka ${SOURCE_FILES} src/start_peak.cpp )
