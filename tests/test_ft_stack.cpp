#include "ft_stack.hpp"

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <deque>
#include <vector>

void TestConstructStack() {
    std::deque<int> mydeque (3,100);          // deque with 3 elements
    std::vector<int> myvector (2,200);        // vector with 2 elements

    ft::stack<int> first;                    // empty stack
    ft::stack<int, std::deque<int> > second (mydeque);         // stack initialized to copy of deque

    assert(first.size() == 0);
    assert(second.size() == mydeque.size());
    assert(second.size() == 3);
    
    ft::stack<int,std::vector<int> > third;  // empty stack using vector
    ft::stack<int,std::vector<int> > fourth (myvector);

    assert(third.size() == 0);
    assert(fourth.size() == myvector.size());
    assert(fourth.size() == 2);
}

void TestSizeStack() {
    ft::stack<int> myints;
    assert(myints.size() == 0);
    assert(myints.empty());

    for (size_t i = 0; i < 5; i++) {
        assert(myints.size() == i);
        myints.push(i);
    }

    assert(myints.size() == 5);

    myints.pop();
    assert(myints.size() == 4);
}

void TestPushPopStack() {
  ft::stack<int> mystack;

  for (size_t i = 0; i < 5; ++i) mystack.push(i);

  std::cout << "Popping out elements...";
  
  while (!mystack.empty()) {
     std::cout << ' ' << mystack.top();
     mystack.pop();
  }
  std::cout << '\n';
}

void TestComparisonStack() {

}

void test_ft_stack() {
    TestConstructStack();
    TestSizeStack();
    TestPushPopStack();
    TestComparisonStack();
    std::cout << "test stack\n";
}