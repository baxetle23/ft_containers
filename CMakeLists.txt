cmake_minimum_required(VERSION 3.16)

project(ft_containers CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++98")

option(BUILD_TEST "Build Tests" ON)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_vector/
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_stack/
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_iterator/
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_map/

)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_vector/ft_vector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_stack/ft_stack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_iterator/ft_iterator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_map/ft_map.cpp
)

add_library(ft_containers SHARED ${SOURCES})

if(BUILD_TEST)
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif(BUILD_TEST)



