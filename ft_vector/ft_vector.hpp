#ifndef FT_VECTOR_H_
#define FT_VECTOR_H_

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
class vector : public vector_base<T, Al> {
private:
    T*      begin_;
    size_t  size_;
    size_t  capacity_;

public:
    //--------------------
    //------TYPEDEF-------
    //--------------------
    typedef ft::vector<T, Al>                           ft_vector;
    typedef ft::vector_base<T, Al>                      vector_base;
    typedef typename vector_base::Altype                allocator_type;
    typedef typename allocator_type::size_type          size_type;
    typedef typename allocator_type::difference_type    difference_type;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::value_type         value_type;
    typedef Ptrit<value_type, difference_type, pointer,
                reference, pointer, reference>          iterator;
    typedef Ptrit<value_type, difference_type,
                const_pointer, const_reference, 
                const_pointer, const_reference>         const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;

    //--------------------
    //-----CONSTRUCT------
    //--------------------
    explicit vector (const allocator_type& alloc = allocator_type()) : vector_base(alloc) {
        allocated_memory(0);
    }

    explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
        vector_base(alloc) {
        allocated_memory(n);
        if (!create_values(n, begin_, val)) {
            throw std::bad_alloc();
        }
    }

    explicit vector (const vector& x);
    
    template <class InputIterator>
    vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

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

    void destroy_values(pointer begin, pointer end) {
        for(; begin != end; ++begin) {
            vector_base::allocator_.destroy(begin);
        }
    }
};
} //namespace ft

#endif