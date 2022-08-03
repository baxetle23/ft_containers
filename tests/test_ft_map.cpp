#include "ft_map.hpp"

#include <cassert>
#include <stdexcept>

#include <functional>
#include <string>
#include <iostream>

void testConstructMap() {
    ft::map<int, std::string> map_less;
    ft::map<int, std::string, std::greater <int>> map_greater;
    size_t size_map = 10;

    //заполняем мапы
    for(size_t i = 0; i < size_map; ++i) {
        map_less[i] = std::to_string(i + 1000);
        map_greater[i] = std::to_string(i + 1000);
    }


    //проверяем порядок ключей согласно функтору
    //от меньшего к большему
    int i = 0;
    for(const auto& pair : map_less) {
        assert(pair.first == i);
        assert(pair.second == std::to_string(i + 1000));
        i++;
    }

    //от большего к меньшему
    i = size_map - 1;
    for(const auto& pair : map_greater) {
        assert(pair.first == i);
        assert(pair.second == std::to_string(i + 1000));
        i--;
    }

    //конструктор присваивания
    ft::map<int, std::string, std::greater<int>> other_map(map_greater);
    assert(other_map.size() == map_greater.size());
    for(size_t i = 0; i < size_map; ++i) {
        assert(other_map[i] == map_greater[i]);
    }
    
}

void testSizeMap() {

}

void testIteratorMap() {

}

void testFindMap() {

}

void testBoundMap() {

}

void testInsertMap() {

}

void testEraseMap() {

}

void testOperatorMap() {

}

void test_ft_map() {
    testConstructMap();
    testSizeMap();
    testIteratorMap();
    testFindMap();
    testBoundMap();
    testInsertMap();
    testEraseMap();
    testOperatorMap();
}