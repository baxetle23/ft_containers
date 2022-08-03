#include <iostream>

void test_ft_vector();
void test_ft_stack();
void test_ft_map();

int main() {
    
    std::cout << "Begin test ..." << std::endl;
    test_ft_vector();
    std::cout << "FT_VECTOR OK\n";
    test_ft_stack();
    std::cout << "FT_STACK OK\n";
    test_ft_map();
    std::cout << "FT_MAP OK\n";
    std::cout << "End test!" << std::endl;
}