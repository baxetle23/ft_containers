#ifndef FT_STACK_H
#define FT_STACK_H

#include "ft_vector.hpp"

namespace ft {

template <typename T, typename C = ft::vector<T> >
class stack {
private:
    C& container;
public:
    typedef typename C::value_type value_type;
    typedef typename C::size_type  size_type;

    explicit stack(const C& container) : container(container) {
    }

    stack() : container() {
    }

    bool empty() const {
        return container.empty();
    }
    
    size_type size() const {
        return container.size();
    }

    value_type& top() {
        return container.back();
    }

    const value_type& top() const {
        return container.back();
    }

    void push(const value_type& element) {
        container.push_back(element);
    }

    void pop_back() {
        container.pop_back();
    }

    bool Eq(const stack<T, C>& other) const {
        return container == other.container;
    }

    bool Lt(const stack<T, C>& other) const {
        return container < other.container;
    }
};

//stack TEMPLATE FUNCTIONS

template <typename T, typename C> inline
bool operator==(const stack<T, C>& lhs, const stack<T, C>& rhs) {
    return lhs.Eq(rhs);
}

template <typename T, typename C> inline
bool operator!=(const stack<T, C>& lhs, const stack<T, C>& rhs) {
    return !(lhs == rhs);
}

template <typename T, typename C> inline
bool operator<(const stack<T, C>& lhs, const stack<T, C>& rhs) {
    return lhs.Lt(rhs);
}

template <typename T, typename C> inline
bool operator>(const stack<T, C>& lhs, const stack<T, C>& rhs) {
    return !lhs.Lt(rhs);
}

template <typename T, typename C> inline
bool operator<=(const stack<T, C>& lhs, const stack<T, C>& rhs) {
    return rhs > lhs;
}

template <typename T, typename C> inline
bool operator>=(const stack<T, C>& lhs, const stack<T, C>& rhs) {
    return !(rhs > lhs);
}


} //namespace ft

#endif