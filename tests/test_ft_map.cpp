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
    size_t size_map = 1000;
    ft::map<int, double> ft_map;

    for(size_t i = 0; i < size_map; ++i) {
        ft_map[i] = i + 0.1;
    }

    assert(ft_map.empty() == false);
    assert(ft_map.size() == size_map);
    assert(ft_map.count(0) == true);
    assert(ft_map.count(1000) == false);
}

void testIteratorMap() {
    ft::map<int, std::string> map;
    map.insert(ft::make_pair(21, "sber"));
    map.insert(ft::make_pair(42, "ecole"));
    
    //iterator
    ft::map<int, std::string>::iterator it = map.begin();
    assert(it->first == 21);
    assert(it->second == "sber");
    ++it;
    assert(it->first == 42);
    assert(it->second == "ecole");
    ++it;
    assert(it == map.end());

    //reverse_iterator
    ft::map<int, std::string>::reverse_iterator rit = map.rbegin();
    assert(rit->first == 42);
    assert(rit->second == "ecole");
    ++rit;
    assert(rit->first == 21);
    assert(rit->second == "sber");
}

void testFindMap() {
    ft::map<char,int> mymap;
    ft::map<char,int>::iterator it;

    mymap['a']=50;
    mymap['b']=100;
    mymap['c']=150;
    mymap['d']=200;

    it = mymap.find('b');

    if (it != mymap.end()) {
        mymap.erase (it);
    }

    assert(mymap.find('a')->second == 50);
    assert(mymap.find('c')->second == 150); 
    assert(mymap.find('d')->second == 200);
    assert(mymap.count('b') == 0);
}

void testBoundMap() {
    ft::map<char,int> mymap;
    ft::map<char,int>::iterator itlow,itup;

    mymap['a']=20;
    mymap['b']=40;
    mymap['c']=60;
    mymap['d']=80;
    mymap['e']=100;

    itlow=mymap.lower_bound ('b');  //iterator on b
    itup=mymap.upper_bound ('d');   //iterator on next d

    assert(itlow->first == 'b');
    assert(itup->first == 'e');

    mymap.erase(itlow,itup);        // erases [itlow,itup)

    // print content:
    ft::map<char,int>::iterator it = mymap.begin();
    assert(it->first == 'a');
    ++it;
    assert(it->first == 'e');
}

void testInsertMap() {
    ft::map<char,int> mymap;

    // first insert function version (single parameter):
    mymap.insert(ft::pair<char,int>('a',100));
    mymap.insert(ft::pair<char,int>('z',200));

    ft::pair<ft::map<char,int>::iterator,bool> ret;
    ret = mymap.insert (ft::pair<char,int>('z',500));
    assert(ret.second == false);
    assert(ret.first->second == 200);

    // second insert function version (with hint position):
    ft::map<char,int>::iterator it = mymap.begin();
    mymap.insert(it, ft::pair<char,int>('b',300));  // max efficiency inserting
    mymap.insert(it, ft::pair<char,int>('c',400));  // no max efficiency inserting

    it = mymap.begin();
    assert(it->first == 'a');
    ++it;
    assert(it->first == 'b');
    ++it;
    assert(it->first == 'c');
    ++it;
    assert(it->first == 'z');
    ++it;

    // third insert function version (range insertion):
    ft::map<char,int> anothermap;
    anothermap.insert(mymap.begin(),mymap.find('c'));
    it = anothermap.begin();
    assert(it->first == 'a');
    ++it;
    assert(it->first == 'b');
}

void testEraseMap() {

}


void test_ft_map() {
    testConstructMap();
    testSizeMap();
    testIteratorMap();
    testFindMap();
    testBoundMap();
    testInsertMap();
    testEraseMap();
}