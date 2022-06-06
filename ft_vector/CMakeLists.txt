cmake_minimum_required(VERSION 3.16)

project (ft_vector)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++98")

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ft_vector.cpp
)

option(DEBUG    "Build programm with debug information"    ON)
option(TEST     "Build programm with unit tests"           ON)


if(DEBUG)
    add_compile_definitions(DEBUG)
endif(DEBUG)

if(TEST)
    add_compile_definitions(TEST)
endif(TEST)

add_executable(ft_vector ${SOURCES})