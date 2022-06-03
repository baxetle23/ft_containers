cmake_minimum_required(VERSION 3.16)

project (ft_vector)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++98")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")


set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(ft_vector ${SOURCES})