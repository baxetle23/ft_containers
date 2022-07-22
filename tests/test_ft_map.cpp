#include "ft_map.hpp"

#include <cassert>
#include <stdexcept>

void testConstructMap() {
    ft::map<int, int> teste;
    std::cout << "size map: " << teste.size() << std::endl;
}

void test_ft_map() {
    testConstructMap();
}