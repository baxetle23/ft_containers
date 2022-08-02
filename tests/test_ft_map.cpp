#include "ft_map.hpp"

#include <cassert>
#include <stdexcept>

#include <string>
#include <iostream>

void testConstructMap() {
    ft::map<int, int> teste;
    std::cout << "size map: " << teste.size() << std::endl;
}

void test_ft_map() {
    testConstructMap();


    ft::map<std::string, int> test;
    test["test1"] = 21;
    test["test2"] = 22;
    test["test3"] = 23;
    test["test4"] = 24;

    ft::pair<std::string, int> test_pair("test5", 25);
    test.insert(test_pair);  

    std::cout << test.size() << std::endl;

    test.erase("test1");

    std::cout << test.size() << std::endl;

    for(const auto& pair : test) {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }

    

  

}