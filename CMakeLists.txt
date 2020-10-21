cmake_minimum_required(VERSION 3.14)
project(GradientOptimization)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -mtune=native -march=native")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif ()

set(SOURCES )

set(LIBS )

#add_library(${PROJECT_NAME} STATIC ${SOURCES})

#target_link_libraries(${PROJECT_NAME} ${LIBS})

add_subdirectory(Test)
add_subdirectory(Examples)

