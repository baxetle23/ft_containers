#ifndef FT_MAP_H_
#define FT_MAP_H_

#include "xtree.hpp"

namespace ft {

//--------------------
//-----CLASS_PAIR-----
//--------------------

template <typename T1, typename T2>
struct pair {
    typedef T1 first_type;
    typedef T2 second_type;

    first_type  first;
    second_type second;

    pair() : first(), second() {
    }

    template<class U, class V>
    pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {
    }

    pair (const first_type& a, const second_type& b) : first(a), second(b) {
    }

    pair& operator=(const pair<first_type, second_type>& other) {
        if (*this == other) {
            return *this;
        }
        this->second = other.second;
        this->first = other.first;
        return *this;
    }
};

template<class T1, class T2>
ft::pair<T1, T2> make_pair(T1 t, T2 u) {
    return ft::pair<T1, T2>(t, u);
};

template<class T1, class T2>
bool	operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs){
    return (lhs.first == rhs.first) && (lhs.second == rhs.second);
};
template<class T1, class T2>
bool	operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs){
    return lhs != rhs;
};
template<class T1, class T2>
bool	operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs){
    return ((lhs.first < rhs.first) || (!(rhs.first < lhs.first) && (lhs.second < rhs.second)));
};
template<class T1, class T2>
bool	operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs){
    return !(rhs < lhs);
};
template<class T1, class T2>
bool	operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs){
    return rhs < lhs;
};
template<class T1, class T2>
bool	operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs){
    return !(lhs < rhs);
};



// template <typename Key, typename T, typename Pred = std::less<Key>, 


}//namespace ft

#endif