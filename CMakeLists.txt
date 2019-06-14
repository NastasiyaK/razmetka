cmake_minimum_required(VERSION 2.8.11)
project(razmetka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -O2 -fPIC")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

include_directories(${PROJECT_SOURCE_DIR}/include)

FILE(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c*)

add_executable(razmetka ${SOURCE_FILES} src/find_VT.cpp src/check_form_of_V_beat.cpp include/point_of_intersection.h src/point_of_intersection.cpp)

target_link_libraries(razmetka m)