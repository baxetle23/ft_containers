#ifndef FT_VECTOR_H_
#define FT_VECTOR_H_

#include <iostream>

#include <memory>
#include <stdexcept>
#include "ft_iterator.hpp"

namespace ft {

template <typename T, typename A>
class vector_base {
protected:
    typedef typename A::template rebind<T>::other Altype;
    
    vector_base (A allocator = A()) : allocator_(allocator) {
    }

    Altype allocator_;
};

template <typename T, typename Al = std::allocator<T> >
class vector : public ft::vector_base<T, Al> {
private:
    T*      begin_;
    size_t  size_;
    size_t  capacity_;

public:
    //--------------------
    //------TYPEDEF-------
    //--------------------
    typedef vector<T, Al>                               my_vector;
    typedef ft::vector_base<T, Al>                      vector_base;
    typedef size_t                                      size_type;
    typedef T                                           value_type;
    
    typedef typename vector_base::Altype                allocator_type;
    typedef typename allocator_type::difference_type    difference_type;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    
    typedef Ptrit<value_type, difference_type, pointer,
                reference, pointer, reference>          iterator;
    typedef Ptrit<value_type, difference_type,
                const_pointer, const_reference, 
                const_pointer, const_reference>         const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

    //--------------------
    //----CONSTRUCTOR-----
    //--------------------
    explicit vector (const allocator_type& alloc = allocator_type()) : vector_base(alloc) {
        #ifdef DEBUG 
            std::cout << "1 construct" << std::endl;
        #endif
        allocated_memory(0);
    }

    explicit vector(size_type n, const T& val = T(), const allocator_type& alloc = allocator_type()) : vector_base(alloc) {
        #ifdef DEBUG
            std::cout << "2 construct" << std::endl;
        #endif
        allocated_memory(n);
        if (!create_values(n, begin_, val)) {
            throw std::bad_alloc();
        }
        size_ = capacity_ = n;
    }

    explicit vector(const my_vector& x) : vector_base(x.allocator_) {
        #ifdef DEBUG
            std::cout << "3 construct" << std::endl;
        #endif
        allocated_memory(x.size_);
        if (!copy_values(x.size_, x.begin_)) {
            throw std::bad_alloc();
        }
        size_ = capacity_ = x.size_;
    }
    
    template <typename InputIterator>
    explicit vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = 0) : vector_base(alloc) {
        #ifdef DEBUG
            std::cout << "4 construct" << std::endl;
        #endif
    }

    ~vector() {
        destroy_values(begin_, begin_ + size_);
        delete_memory();
    }
    
    
    //--------------------
    //-----ITERATORS------
    //--------------------
    iterator begin() {
        return iterator(begin_);
    }

    const_iterator begin() const {
        return const_iterator(begin_);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    iterator end() {
        return iterator(begin_ + size_);
    }

    const_iterator end() const {
        return const_iterator(begin_ + size_);
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    //--------------------
    //-----PUBLIC_FUN-----
    //--------------------
    my_vector& operator=(const my_vector& other) {
        if (this == &other) {
            return *this;
        }

        if (other.size() > capacity()) {
            my_vector tmp(other);
            swap(tmp);
        } else {

        }
    }

    void reserve(size_type n) {

    }

    size_type capacity() const {
        return capacity_;
    }

    void resize(size_type n, const value_type& val = value_type()) {
        if (size() < n) {
            insert(end(), n - size(), val);
        } else if (size() > n) {
            erase(begin() + n, end());
        }
    }

    size_type size() const {
        return size_;
    }

    size_type max_size() const {
        return vector_base::allocator_.max_size();
    }

    bool empty() const {
        return size_ == 0;
    }

    allocator_type get_allocator() const {
        return my_vector::allocator_;
    }

    const_reference at(size_type n) const {
        if (size() <= n) {
            throw std::out_of_range("operator at");
        }
        return *(begin() + n);
    }

    reference at(size_type n) {
        if (size() <= n) {
            throw std::out_of_range("operator at");
        }
        return *(begin() + n);
    }

    const_reference operator[](size_type n) const {
        return *(begin() + n);
    }

    reference operator[](size_type n) {
        return *(begin() + n);
    }

    const_reference front() const {
        return *begin();
    }

    reference front() {
        return *begin();
    }

    const_reference back() const {
        return *(end() - 1);
    }

    reference back() {
        return *(end() - 1);
    }

    void push_back(const value_type& val) {
        insert(end(), val);
    }

    void pop_back() {
        erase(end() - 1);
    }

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last) {

    }

    void assign (size_type n, const value_type& val) {

    }

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last) {

    }

    iterator insert(iterator position, const value_type& val) {

    }

    void insert(iterator position, size_type n, const value_type& val) {

    }

    iterator erase (iterator position) {

    }

    iterator erase (iterator first, iterator last) {

    }

    void swap (my_vector& x) {

    }

    void clear() {

    }
    
    //--------------------
    //----PRIVATE_FUN-----
    //--------------------
private:
    bool allocated_memory(size_type n) {
        begin_ = NULL;
        size_  = 0;
        capacity_ = 0;
        if (n) {
            begin_ = vector_base::allocator_.allocate(n, (void *)0);
            return true;
        }
        return false;
    }

    void delete_memory() {
        vector_base::allocator_.deallocate(begin_, capacity_);
    }

    bool create_values(size_type n, pointer begin_to_fill, const T& value) {
        pointer tmp = begin_to_fill;
        try {
            for (; 0 < n; --n, ++tmp) {
                vector_base::allocator_.construct(tmp, value);
            }
            return true;
        } catch (...) {
            destroy_values(begin_to_fill, tmp);
            return false;
        }
    }

    bool copy_values(size_type n, pointer begin_to_fill) {
        pointer tmp = begin_to_fill;
        try {
            for (; 0 < n; --n, ++tmp) {
                vector_base::allocator_.construct(tmp, *tmp);
                return true;
            }
        } catch (...) {
            destroy_values(begin_to_fill, tmp);
            return false;
        }
    }

    void destroy_values(pointer begin, pointer end) {
        for(; begin != end; ++begin) {
            vector_base::allocator_.destroy(begin);
        }
    }
};

//--------------------
//----TEMPLATE_FUN----
//--------------------
template <typename T, typename A> inline
bool operator==(const vector<T, A>& X, const vector<T, A>& Y) {

}

template <typename T, typename A> inline
bool operator!=(const vector<T, A>& X, const vector<T, A>& Y) {

}

template <typename T, typename A> inline
bool operator<(const vector<T, A>& X, const vector<T, A>& Y) {

}

template <typename T, typename A> inline
bool operator>(const vector<T, A>& X, const vector<T, A>& Y) {

}

template <typename T, typename A> inline
bool operator<=(const vector<T, A>& X, const vector<T, A>& Y) {

}

template <typename T, typename A> inline
bool operator>=(const vector<T, A>& X, const vector<T, A>& Y) {

}

template <typename T, typename A> inline
void swap(const vector<T, A>& X, const vector<T, A>& Y) {

}

} //namespace ft

#endif