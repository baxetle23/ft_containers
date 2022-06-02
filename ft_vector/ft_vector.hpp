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

    //--------------------
    //-----CONSTRUCT------
    //--------------------
    explicit vector (const allocator_type& alloc = allocator_type()) : vector_base(alloc) {
    }

    explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
    explicit vector (const vector& x);
    
    template <class InputIterator>
    vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

    //--------------------
    //----PRIVATE_FUN-----
    //--------------------
private:

};
} //namespace ft

#endif