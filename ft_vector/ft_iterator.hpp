#ifndef FT_ITERATOR_H_
#define FT_ITERATOR_H_

#include <utility>

namespace ft {

//--------------------
//----TAG_ITERATOR----
//--------------------
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
struct Int_iterator_tag {};


//--------------------
//------ITERATOR------
//--------------------
template <typename C, typename T, typename D = std::ptrdiff_t, typename Pt = T*, typename Rt = T&>
struct iterator {
    typedef C   iterator_category;
    typedef T   value_type;
    typedef D   difference_type;
    typedef Pt  pointer;
    typedef Rt  reference;
};

template <typename T, typename D, typename Pt, typename Rt>
struct Bidit : public iterator<bidirectional_iterator_tag, T, D, Pt, Rt> {};

template <typename T, typename D, typename Pt, typename Rt>
struct Ranit : public iterator<random_access_iterator_tag, T, D, Pt, Rt> {};


//--------------------
//---ITERATOR_TRAITS--
//--------------------
template <typename It>
struct iterator_traits {
    typedef typename It::iterator_category  iterator_category;
    typedef typename It::value_type         value_type;
    typedef typename It::difference_type    difference_type;
    typedef typename It::pointer            pointer;
    typedef typename It::refernce           reference;
};

template <typename T>
struct iterator_traits<T*> {
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef std::ptrdiff_t              difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};

template <typename T>
struct iterator_traits<const T*> {
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef std::ptrdiff_t              difference_type;
    typedef const T*                    pointer;
    typedef const T&                    reference;
};

//--------------------
//----ITERATOR_CAT----
//--------------------

} // namespace ft


#endif