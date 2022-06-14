cmake_minimum_required(VERSION 3.16)

project(ft_containers CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++98")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_vector/
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_iterator/
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_vector/ft_vector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ft_iterator/ft_iterator.cpp
)

add_library(_ftcontainers SHARED ${SOURCES})

option(BUILD_TEST "Build Tests" ON)

if(BUILD_TEST)
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif(BUILD_TEST)



