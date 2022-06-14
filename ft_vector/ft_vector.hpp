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
        begin_ = NULL;
        size_ = capacity_ = 0;
    }

    explicit vector(size_type n, const T& val = T(), const allocator_type& alloc = allocator_type()) : vector_base(alloc) {
        allocated_memory(n);
        if (!create_values(n, begin_, val)) {
            throw std::bad_alloc();
        }
        size_ = capacity_ = n;
    }

    explicit vector(const my_vector& x) : vector_base(x.allocator_) {
        allocated_memory(x.size_);
        if (!copy_values(x.size_, x.begin_, begin_)) {
            throw std::bad_alloc();
        }
        size_ = capacity_ = x.size_;
    }

    template <typename InputIterator>
    explicit vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = 0) : vector_base(alloc) {
        insert(first, last);
    }

    ~vector() {
        if (size()) {
            destroy_values(begin_, size_);
        }
        if (capacity()) {
            delete_memory(begin_, capacity_);
        }
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
        my_vector tmp(other);
        swap(tmp);
        return *this;
    }

    void reserve(size_type new_capacity) {
        if (new_capacity <= capacity()) {
            return ;
        } else {
            pointer new_mem = vector_base::allocator_.allocate(new_capacity, 0);
            copy_values(size_, begin_, new_mem);
            if (size()) {
                destroy_values(begin_, size_);
            }
            if (capacity()) {
                delete_memory(begin_, capacity_);
            }

            begin_ = new_mem;
            capacity_ = new_capacity;
        }
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
            throw std::out_of_range("out of range");
        }
        return *(begin() + n);
    }

    reference at(size_type n) {
        if (size() <= n) {
            throw std::out_of_range("out of range");
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
    void assign (InputIterator first, InputIterator last,
                 typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = 0) {
        erase(begin(), end());
        insert(begin(), first, last);
    }

    void assign (size_type n, const value_type& val) {
        erase(begin(), end());
        insert(begin(), n, val);
    }

    template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last,
                 typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = 0) {
        size_type size_insert  = last - first;

        if (size_insert <= 0) {
            return ;
        } else if (max_size() - size() < size_insert) {
            throw std::out_of_range("insert range too long");
        } else if (size_insert + size_ > capacity_) {
            // need allocate new memory
            size_type new_capacity = (size_ + size_insert) * 2;
            pointer new_mem = vector_base::allocator_.allocate(new_capacity, 0);
            size_type size_prefix_old_value = position - begin();
            try {
                copy_values(size_prefix_old_value, begin_, new_mem);
                copy_values(size_insert, new_mem + size_prefix_old_value, first);
                copy_values(size_ - size_prefix_old_value, begin_ + size_prefix_old_value, new_mem + size_insert + size_prefix_old_value);
            } catch(...) {
                delete_memory(new_mem, new_capacity);
                throw;
            }

            if (size()) {
                destroy_values(begin_, size_);
            }
            if (capacity()) {
                delete_memory(begin_, capacity_);
            }

            begin_ = new_mem;
            capacity_ = new_capacity;
            size_ += size_insert;
        } else {
            // dont allocate new memory
            size_type size_prefix_old_value = position - begin();
            size_type size_postfix_old_value = end() - position;
            my_vector tmp(begin(), end());
            destroy_values(position, size_postfix_old_value);
            copy_values(size_insert, first, position);
            copy_values(size_postfix_old_value, tmp.begin(), begin() + size_insert + size_prefix_old_value);
            size_ += size_insert;

        }
    }

    iterator insert(iterator position, const value_type& val) {
        size_type offset = size() == 0 ? 0 : position - begin();
        insert(position, 1, val);
        return begin() + offset;
    }

    void insert(iterator position, size_type size_insert, const value_type& val) {
        if (size_insert <= 0) {
            return ;
        } else if (max_size() - size() < size_insert) {
            throw std::out_of_range("insert range too long");
        } else if (size_insert + size_ > capacity_) {

            size_type new_capacity = (size_ + size_insert) * 2;
            pointer new_mem = vector_base::allocator_.allocate(new_capacity, 0);
            size_type size_prefix_old_value = position - begin();
            try {
                copy_values(size_prefix_old_value, begin_, new_mem);
                create_values(size_insert, new_mem + size_prefix_old_value, val);
                copy_values(size_ - size_prefix_old_value, begin_ + size_prefix_old_value, new_mem + size_insert + size_prefix_old_value);
            } catch(...) {
                delete_memory(new_mem, new_capacity);
                throw;
            }

            if (size()) {
                destroy_values(begin_, size_);
            }
            if (capacity()) {
                delete_memory(begin_, capacity_);
            }

            begin_ = new_mem;
            capacity_ = new_capacity;
            size_ += size_insert;
        } else {
            // dont allocate new memory
            size_type size_prefix_old_value = position - begin();
            size_type size_postfix_old_value = end() - position;
            my_vector tmp(*this);
            destroy_values(position.base(), size_postfix_old_value);
            create_values(size_insert, position.base(), val);
            copy_values(size_postfix_old_value, tmp.begin().base() + size_prefix_old_value, begin().base() + size_insert + size_prefix_old_value);
            size_ += size_insert;
        }
    }

    iterator erase(iterator position) {
        std::copy(position + 1, end(), position);
        destroy_values(&back(), 1);
        --size_;
        return position;
    }

    iterator erase(iterator first, iterator last) {
        if (first != last) {
            pointer new_end = std::copy(last, end(), first.base());
            destroy_values(new_end, last - first);
            size_ -= (last - first);
        }
        return first;
    }

    void swap (my_vector& x) {
        std::swap(begin_, x.begin_);
        std::swap(size_, x.size_);
        std::swap(capacity_, x.capacity_);
    }

    void clear() {
        erase(begin(), end());
    }

    bool Eq(const my_vector& other) const {
        return (size_ == other.size_ && std::equal(begin(), end(), other.begin()));
    }

    bool Lt(const my_vector& other) const {
        return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
    }

    //--------------------
    //----PRIVATE_FUN-----
    //--------------------
private:
    bool allocated_memory(size_type n) {
        if (n) {
            begin_ = vector_base::allocator_.allocate(n, (void *)0);
            return true;
        }
        return false;
    }

    //освобождаем память по указателю и количеству
    void delete_memory(pointer begin_to_delete, size_type count) {
        vector_base::allocator_.deallocate(begin_to_delete, count);
    }

    //разрушаем объекты по указателю и количеству
    void destroy_values(pointer begin_to_destroy, size_type count) {
        for(; 0 < count; ++begin_to_destroy, --count) {
            vector_base::allocator_.destroy(begin_to_destroy);
        }
    }

    bool create_values(size_type n, pointer begin_to_fill, const T& value) {
        pointer tmp = begin_to_fill;
        try {
            for (; 0 < n; --n, ++tmp) {
                vector_base::allocator_.construct(tmp, value);
            }
            return true;
        } catch (...) {
            destroy_values(begin_to_fill, tmp - begin_to_fill);
            return false;
        }
    }

    bool copy_values(size_type n, pointer src, pointer dst) {
        pointer tmp = dst;
        try {
            for (; 0 < n; --n, ++dst, ++src) {
                vector_base::allocator_.construct(dst, *src);
            }
        } catch (...) {
            destroy_values(tmp, dst - tmp);
            return false;
        }
        return true;
    }
};

//--------------------
//----TEMPLATE_FUN----
//--------------------
template <typename T, typename A> inline
bool operator==(const vector<T, A>& X, const vector<T, A>& Y) {
    return X.Eq(Y);
}

template <typename T, typename A> inline
bool operator!=(const vector<T, A>& X, const vector<T, A>& Y) {
    return !(X == Y);
}

template <typename T, typename A> inline
bool operator<(const vector<T, A>& X, const vector<T, A>& Y) {
    return X.Lt(Y);
}

template <typename T, typename A> inline
bool operator>(const vector<T, A>& X, const vector<T, A>& Y) {
    return Y < X;
}

template <typename T, typename A> inline
bool operator<=(const vector<T, A>& X, const vector<T, A>& Y) {
    return !(Y < X);
}

template <typename T, typename A> inline
bool operator>=(const vector<T, A>& X, const vector<T, A>& Y) {
    return !(X < Y);
}

template <typename T, typename A> inline
void swap(const vector<T, A>& X, const vector<T, A>& Y) {
    X.swap(Y);
}

} //namespace ft

#endif
