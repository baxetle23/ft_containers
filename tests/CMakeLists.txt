cmake_minimum_required(VERSION 3.16)

project(test_containers)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../ft_vector/
    ${CMAKE_CURRENT_SOURCE_DIR}/../ft_stack/
    ${CMAKE_CURRENT_SOURCE_DIR}/../ft_map/
)

add_link_options(-l_ftcontainers)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../build/)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g -std=c++17")

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ft_vector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ft_stack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ft_map.cpp
)

add_executable(test_containers ${SOURCES})
