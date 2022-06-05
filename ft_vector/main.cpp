#include "ft_vector.hpp"
#include <iostream>
#include <vector>

void test_vector();

int main() {
    ft::vector<int> test1((size_t)10, 12);
    ft::vector<int> test(10);
    ft::vector<int> test3(test1);


    std::cout << "print vector1 : ";
    for(const auto& el : test1) {
        std::cout << el << " ";
    }

    std::cout << "print vector2 : ";
    for(ft::vector<int>::iterator it = test1.begin(); it != test1.end(); ++it) {
        std::cout << *it << " ";
    }
}