#ifndef FT_VECTOR_H_
#define FT_VECTOR_H_

#include <memory>
#include <stdexcept>

namespace ft {

template <typename T>
class vector {
private:
    T*      begin_;
    size_t  size_;
    size_t  capacity_;
public:
    vector() : begin_(NULL), size_(0), capacity_(0) {

    }

    void Hello() const {
        std::cout << "first step\n";
    }
};
} //namespace ft

#endif