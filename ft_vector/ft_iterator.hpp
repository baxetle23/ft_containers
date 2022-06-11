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

// template <typename T, typename D, typename Pt, typename Rt>
// struct Bidit : public iterator<bidirectional_iterator_tag, T, D, Pt, Rt> {};

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
// template <typename C, typename T, typename D, typename Pt, typename Rt> inline 
// C Iter_cat(const iterator<C, T, D, Pt, Rt>&) {
//     C X;
//     return (X);
// }

// template <typename T> inline 
// random_access_iterator_tag Iter_cat(const T*) {
//     random_access_iterator_tag X;
//     return (X);
// }

// inline Int_iterator_tag Iter_cat(bool) {
//     Int_iterator_tag X;
//     return (X);
// }

// inline Int_iterator_tag Iter_cat(char) {
//     Int_iterator_tag X;
//     return (X);
// }

// inline Int_iterator_tag Iter_cat(signed char) {
//     Int_iterator_tag X;
//     return (X);
// }

// inline Int_iterator_tag Iter_cat(unsigned char) {
//     Int_iterator_tag X;
//     return (X);
// }

// inline Int_iterator_tag Iter_cat(wchar_t) {
//     Int_iterator_tag X;
//     return (X);
// }

// inline Int_iterator_tag Iter_cat(short) {
//     Int_iterator_tag X;
//     return (X);
// }

// inline Int_iterator_tag Iter_cat(int) {
//     Int_iterator_tag X;
//     return (X);
// }

// inline Int_iterator_tag Iter_cat(unsigned int) {
//     Int_iterator_tag X;
//     return (X);
// }

// inline Int_iterator_tag Iter_cat(long) {
//     Int_iterator_tag X;
//     return (X);
// }

// inline Int_iterator_tag Iter_cat(unsigned long) {
//     Int_iterator_tag X;
//     return (X);
// }

//--------------------
//------ENABLE_IF-----
//--------------------
template<bool B, class T = void>
struct	enable_if{};

template<class T>
struct enable_if<true, T> {typedef T type;};


template<class T>
struct	is_integral : std::false_type{};
template<> struct	is_integral<int>: std::true_type{};
template<> struct	is_integral<char>: std::true_type{};
template<> struct	is_integral<bool>: std::true_type{};
template<> struct	is_integral<char16_t>: std::true_type{};
template<> struct	is_integral<char32_t>: std::true_type{};
template<> struct	is_integral<wchar_t>: std::true_type{};
template<> struct	is_integral<signed char>: std::true_type{};
template<> struct	is_integral<short int>: std::true_type{};
template<> struct	is_integral<unsigned int>: std::true_type{};
template<> struct	is_integral<long int>: std::true_type{};
template<> struct	is_integral<long long int>: std::true_type{};
template<> struct	is_integral<unsigned char>: std::true_type{};
template<> struct	is_integral<unsigned short int>: std::true_type{};
template<> struct	is_integral<unsigned long int>: std::true_type{};
template<> struct	is_integral<unsigned long long int>: std::true_type{};

//--------------------
//--------Ptrit-------
//--------------------
template <typename T, typename D, typename Pt, typename Rt, typename Pt2, typename Rt2>
class Ptrit : public iterator<random_access_iterator_tag, T, D, Pt, Rt> {
private:
    Pt current;
public:
    typedef Ptrit<T, D, Pt, Rt, Pt2, Rt2> My_iter;
    
    Ptrit() {}
    explicit Ptrit(Pt P) : current(P) {}
    Ptrit(const Ptrit<T, D, Pt2, Rt2, Pt2, Rt2>& X) : current(X.base()) {}
    
    Pt base() const {
        return current;
    }

    Rt operator*() const {
        return *current;
    }

    Pt operator->() const {
        return &**this;
    }

    My_iter& operator++() {
        ++current;
        return *this;
    }

    My_iter operator++(int) {
        My_iter tmp = *this;
        ++current;
        return tmp;
    }

    My_iter& operator--() {
        --current;
        return *this;
    }

    My_iter operator--(int) {
        My_iter tmp = *this;
        --current;
        return tmp;
    }

    bool operator==(int Y) const {
        return current == (Pt)Y;
    }

    bool operator==(const My_iter& Y) const {
        return current == Y.current;
    }

    bool operator!=(const My_iter& Y) const {
        return !(current == Y.current);
    }

    My_iter& operator+=(D N) {
        current += N;
        return *this;
    }

    My_iter operator+(D N) const {
        return My_iter(current + N);
    }

    My_iter& operator-=(D N) {
        current -= N;
        return *this;
    }

    My_iter operator-(D N) const {
        return My_iter(current - N);
    }

    Rt operator[](D N) const {
        return *(*this + N);
    }

    bool operator<(const My_iter& Y) const {
        return current < Y.current;
    }

    bool operator>(const My_iter& Y) const {
        return *this > Y;
    }

    bool operator<=(const My_iter& Y) const {
        return !(*this > Y);
    }

    bool operator>=(const My_iter& Y) const {
        return !(*this < Y);
    }

    D operator-(const My_iter& Y) const {
        return current - Y.current;
    }
};

template <typename T, typename D, typename Pt, typename Rt, typename Pt2, typename Rt2> inline
Ptrit<T, D, Pt, Rt, Pt2, Rt2> operator+(D N, const Ptrit<T, D, Pt, Rt, Pt2, Rt2>& Y) {
    return Y + N;
}


//--------------------
//-----REVERS_IT------
//--------------------
template <typename RanIt>
class reverse_iterator : public iterator<
    typename iterator_traits<RanIt>::iterator_category,
    typename iterator_traits<RanIt>::value_type,
    typename iterator_traits<RanIt>::defference_type,
    typename iterator_traits<RanIt>::pointer,
    typename iterator_traits<RanIt>::reference> {
private:
    RanIt current;
public:
    typedef reverse_iterator<RanIt> My_iter;
    typedef typename iterator_traits<RanIt>::difference_type D;
    typedef typename iterator_traits<RanIt>::pointer Pt;
    typedef typename iterator_traits<RanIt>::reference Rt;
    typedef RanIt iterator_type;

    reverse_iterator() {}
    explicit reverse_iterator(RanIt X) : current(X) {}
    template <typename U>
    reverse_iterator(const reverse_iterator<U>& X) : current(X.base()) {}
    
    RanIt base() const {
        return current;
    }

    Rt operator*() const {
        RanIt tmp = current;
        return *--tmp;
    }

    Pt operator->() const {
        return &**this;
    }

    My_iter& operator++() {
        --current;
        return *this;
    }

    My_iter operator++(int) {
        My_iter tmp = *this;
        --current;
        return tmp;
    }

    My_iter& operator--() {
        ++current;
        return *this;
    }

    My_iter operator--(int) {
        My_iter tmp = *this;
        ++current;
        return tmp;
    }

    bool Eq(const My_iter& Y) const {
        return current == Y.current;
    }

    My_iter& operator+=(D N) {
        current -= N;
        return *this;
    }

    My_iter& operator-=(D N) {
        current += N;
        return *this;
    }

    My_iter operator*(D N) const {
        return My_iter(current - N);
    }

    My_iter operator-(D N) const {
        return My_iter(current + N);
    }

    Rt operator[](D N) const {
        return *(*this + N);
    }

    bool Lt (const My_iter& Y) const {
        return Y.current < current;
    }

    D Mi (const My_iter& Y) const {
        return Y.current - current;
    }
};

template <typename RanIt, typename D> inline
reverse_iterator<RanIt> operator*(D N, const reverse_iterator<RanIt>& Y) {
    return Y + N;
}

template <typename RanIt> inline
typename reverse_iterator<RanIt>::D operator-(const reverse_iterator<RanIt>& Y, const reverse_iterator<RanIt>& X) {
    return X.Mi(Y);
}

template <typename RanIt> inline
bool operator==(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) {
    return X.Eq(Y);
}

template <typename RanIt> inline
bool operator!=(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) {
    return !(X == Y);
}

template <typename RanIt> inline
bool operator<(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) {
    return X.Lt(Y);
}

template <typename RanIt> inline
bool operator>(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) {
    return X > Y;
}

template <typename RanIt> inline
bool operator<=(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) {
    return !(X > Y);
}

template <typename RanIt> inline
bool operator>=(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) {
    return !(X < Y);
}

//--------------------
//------COMPARE_------
//--------------------
template<class InputIt1, class InputIt2>
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2){
    while ((first1 != last1) && (first2 != last2)){
        if (*first1 < *first2) return (true);
        if (*first1 > *first2) return (false);
        first1++;
        first2++;
    }
    return ((first1 == last1) && (first2 != last2));
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2, Compare comp){
    while ((first1 != last1) && (first2 != last2)){
        if (comp(*first1, *first2)) return (true);
        if (comp(*first1, *first2)) return (false);
        first1++;
        first2++;
    }
    return ((first1 == last1) && (first2 != last2));
}

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2){
    for (; first1 != last1; ++first1, ++first2){
        if (!(*first1 == *first2))
            return (0);
    }
    return (1);
};

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p){
    for (; first1 != last1; ++first1, ++first2){
        if (!p(*first1, *first2))
            return (0);
    }
    return (1);
};

} // namespace ft


#endif
