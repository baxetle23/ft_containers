cmake_minimum_required(VERSION 3.16)

project (ft_vector)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++98")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -std=c++98")


set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ft_vector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_executable(ft_vector ${SOURCES})