#ifndef XTREE_H_
#define XTREE_H_

#include "ft_iterator.hpp"
#include <iterator>

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

template<typename Tr>
class Tree_nod : public Tr {
protected:
    typedef typename Tr::allocator_type     allocator_type;
    typedef typename Tr::key_compare        key_compare;
    typedef typename Tr::value_type         value_type;
    typedef typename allocator_type::template
            rebind<void>::other::pointer    Genptr;

struct Node {
    Genptr Left, Right, Parent;
    value_type Value;
    char Collor, Isnil;
};

Tree_nod(const key_compare& Parg, allocator_type Al) : Tr(Parg), Alnod(Al) {
}

typename allocator_type::template
    rebind<Node>::other Alnod;
};

template <typename Tr>
class Tree_ptr : public Tree_nod<Tr> {
protected:
    typedef typename Tree_nod<Tr>::Node Node;
    typedef typename Tr::allocator_type allocator_type;
    typedef typename Tr::key_compare key_compare;
    typedef typename allocator_type::template
        rebind<Node>::other::pointer Nodeptr;
    
    Tree_ptr (const key_compare& Parg, allocator_type Al) : Tree_nod<Tr>(Parg, Al), Alptr(Al) {
    }

    typename allocator_type::template
        rebind<Nodeptr>::other Alptr;
};

template <typename Tr>
class Tree_val : public Tree_ptr<Tr> {
protected:
    typedef typename Tr::allocator_type allocator_type;
    typedef typename Tr::key_compare key_compare;
    
    Tree_val (const key_compare& Parg, allocator_type Al) : Tree_ptr<Tr>(Parg, Al), Alval(Al) {
    }
    allocator_type Alval;
};

template <typename Tr>
class Tree : public Tree_val<Tr> {
public:
    typedef Tree<Tr>                    Mytree;
    typedef Tree_val<Tr>                Mybase;
    typedef typename Tr::key_type       key_type;
    typedef typename Tr::key_compare    key_compare;
    typedef typename Tr::value_compare  value_compare;
    typedef typename Tr::value_type     value_type;
    typedef typename Tr::allocator_type allocator_type;
protected:
    typedef typename Tree_nod<Tr>::Genptr           Genptr;
    typedef typename Tree_nod<Tr>::Node             Node;
    enum Redbl {Red, Black};
    typedef typename allocator_type::template
        rebind<Node>::other::pointer              Nodeptr;
    typedef typename allocator_type::template
        rebind<Nodeptr>::other::reference         Nodepref;
    typedef typename allocator_type::template
        rebind<key_type>::other::const_reference  Keyref;
    typedef typename allocator_type::template
        rebind<char>::other::reference            Charref;
    typedef typename allocator_type::template
        rebind<value_type>::other::reference      Vref;

    static Charref Color(Nodeptr P) {
        return ((Charref)(*P).Color);
    }
    static Charref Isnil(Nodeptr P) {
        return ((Charref)(*P).Isnil);
    }
    static Keyref Key(Nodeptr P) {
        return ((Keyref)(Value(P)));
    }
    static Nodepref Left(Nodeptr P) {
        return ((Nodepref)(*P).Left);
    }
    static Nodepref Parent(Nodeptr P) {
        return ((Nodepref)(*P).Parent);
    }
    static Nodepref Right(Nodeptr P) {
        return ((Nodepref)(*P).Right);
    }
    static Vref Value(Nodeptr P) {
        return ((Vref)(*P).Value);
    }

public:
    typedef typename allocator_type::size_type          size_type;
    typedef typename allocator_type::difference_type    Dift;
    typedef typename allocator_type::template
        rebind<value_type>::other::pointer              Tptr;
    typedef typename allocator_type::template
        rebind<value_type>::other::const_pointer        Ctptr;
    typedef typename allocator_type::template
        rebind<value_type>::other::reference            Reft;
    typedef typename allocator_type::template
        rebind<value_type>::other::const_reference     const_reference;
    

    typedef Dift    difference_type;
    typedef Tptr    pointer;
    typedef Ctptr   const_pointer;
    typedef Reft    reference;


    //class iterator
    class iterator;
    friend class iterator;
    class iterator : public ft::Bidit<value_type, Dift, Tptr, Reft> {
    protected:
        Nodeptr Ptr;
    public:
        typedef ft::Bidit<value_type, Dift, Tptr, Reft> Mybase;
        typedef typename Mybase::iterator_category              iterator_category;
        typedef typename Mybase::difference_type                difference_type;
        typedef typename Mybase::pointer                        pointer;
        typedef typename Mybase::reference                      reference;
    
        iterator() : Ptr(0) {}
        iterator(Nodeptr ptr) : Ptr(ptr) {}

        reference operator*() const {
            return Value(Ptr);
        }

        Tptr operator->() const {
            return &**this;
        }
        iterator operator++() {
            Inc();
            return *this;
        }
        iterator operator++(int) {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }
        iterator operator--() {
            Dec();
            return *this;
        }
        iterator operator--(int) {
            iterator tmp = *this;
            --*this;
            return tmp;
        }
        bool operator==(const iterator other) const {
            return Ptr == other.Ptr;
        }
        bool operator!=(const iterator other) const {
            return !(*this == other);
        }
        void Dec() {
            if (isnil(Ptr)) {
                Ptr == Right(Ptr);
            } else if (!Isnil(Left(Ptr))) {
                Ptr = Max(Left(Ptr));
            } else {
                Nodeptr P;
                while(!Isnil(P = Parent(Ptr)) && Ptr == Left(Ptr)) {
                    Ptr = P;
                }
                if (!Isnil(P)) {
                    Ptr = P;
                }
            }
        }
        void Inc() {
            if (Isnil(Ptr)) {
                ;
            } else if (Isnil(Right(Ptr))) {
                Ptr = Min(Right(Ptr));
            } else {
                Nodeptr P;
                while (!Isnil(P = Parent(Ptr)) && Ptr =- Right(P)) {
                    Ptr = P;
                }
                Ptr = P;
            }
        }
        Nodeptr Mynode() const {
            return Ptr;
        }
    };

    //class const_iterator
    class const_iterator;
    friend class const_iterator;
    class const_iterator : public ft::Bidit<value_type, Dift, Ctptr, const_reference> {
    protected:
        Nodeptr Ptr;
    public:
        typedef ft::Bidit<value_type, Dift, Ctptr, const_reference> Mybase;
        typedef typename Mybase::iterator_category                  iterator_category;
        typedef typename Mybase::difference_type                    difference_type;
        typedef typename Mybase::pointer                            pointer;
        typedef typename Mybase::reference                          reference;
    
        const_iterator() : Ptr(0) {}
        const_iterator(Nodeptr ptr) : Ptr(ptr) {}
        const_iterator(const typename Tree<Tr>::iterator it) : Ptr(it.Mynode()) {}

        const_reference operator*() const {
            return Value(Ptr);
        }

        Ctptr operator->() const {
            return &**this;
        }
        const_iterator operator++() {
            Inc();
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++*this;
            return tmp;
        }
        const_iterator operator--() {
            Dec();
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator tmp = *this;
            --*this;
            return tmp;
        }
        bool operator==(const const_iterator other) const {
            return Ptr == other.Ptr;
        }
        bool operator!=(const const_iterator other) const {
            return !(*this == other);
        }
        void Dec() {
            if (isnil(Ptr)) {
                Ptr == Right(Ptr);
            } else if (!Isnil(Left(Ptr))) {
                Ptr = Max(Left(Ptr));
            } else {
                Nodeptr P;
                while(!Isnil(P = Parent(Ptr)) && Ptr == Left(Ptr)) {
                    Ptr = P;
                }
                if (!Isnil(P)) {
                    Ptr = P;
                }
            }
        }
        void Inc() {
            if (Isnil(Ptr)) {
                ;
            } else if (Isnil(Right(Ptr))) {
                Ptr = Min(Right(Ptr));
            } else {
                Nodeptr P;
                while (!Isnil(P = Parent(Ptr)) && Ptr =- Right(P)) {
                    Ptr = P;
                }
                Ptr = P;
            }
        }
        Nodeptr Mynode() const {
            return Ptr;
        }
    };

    typedef std::reverse_iterator<iterator>             reverse_iterator;
    typedef std::reverse_iterator<const_iterator>       const_reverse_iterator;
    typedef ft::pair<iterator, bool>                    Pairib;
    typedef ft::pair<iterator, iterator>                Pairii;
    typedef ft::pair<const_iterator, const_iterator>    Paircc;

    explicit Tree(const key_compare& Parg, const allocator_type& Al) : Mybase(Parg, Al) {
        Init();
    }
    Tree(const value_type *F, const value_type *L, const key_compare& Parg, const allocator_type& Al) :
        Mybase(Parg, Al) {
            Init();
            insert(F, L);
    }
    Tree(const Mytree& other) : Mybase(other.key_comp(), other.get_allocator()) {
        Init();
        Copy(other);
    }
    ~Tree() {
        erase(begin(), end());
        Freenode(Head);
        Head = 0;
        Size = 0;
    }

    Mytree& operator=(const Mytree& other) {

    }
    iterator begin() {

    }
    const_iterator begin() const {

    }
    iterator end() {

    }
    const_iterator end() const {

    }
    reverse_iterator rbegin() {

    }
    const_reverse_iterator rbegin() const {

    }
    reverse_iterator rend() {

    }
    const_reverse_iterator rend() const {

    }


    size_type size() const {

    }
    size_type max_size() const {

    }
    bool empty() const {

    }
    allocator_type get_allocator() const {

    }
    key_compare key_comp() const {
    
    }
    value_compare value_comp() const {

    }
    Pairib insert(const value_type& val) {

    }
    iterator insert(iterator P, const value_type& val) {

    }
    template<typename It>
    void insert(It F, It L) {

    }
    iterator erase(iterator P) {

    }
    iterator erase(iterator F, iterator L) {

    }
    size_type erase(const key_type& X) {

    }
    void erase(const key_type *F, const key_type *L) {

    }
    void clear() {

    }
    iterator find(const key_type& Kv) {

    }
    const_iterator find(const key_type& Kv) const {

    }
    size_type count(const key_type& Kv) const {

    }
    iterator lower_bound(const key_type& Kv) {

    }
    const_iterator lower_bound(const key_type& Kv) const {

    }
    iterator upper_bound(const key_type& Kv) {

    }
    const_iterator upper_bound(const key_type& Kv) const {

    }
    Pairii equal_range(const key_type& Kv) {

    }
    Paircc equal_range(const key_type& Kv) const {

    }
    void swap(Mytree& X) {
        
    }

protected:
    void Copy(const Mytree& other) {

    }
    Nodeptr Copy(Nodeptr X, Nodeptr Y) {

    }
    void Erase(Nodeptr node) {

    }
    void Init() {

    }
    iterator Insert(bool Addleft, Nodeptr Y, const value_type& v) {

    }
    Nodeptr Lbound(const key_type& Kv) const {

    }
    Nodeptr& Lmost() {
        
    }
    Nodeptr& Lmost() const {
        
    }
    Nodeptr& Rmost() {
        
    }
    Nodeptr& Rmost() const {
        
    }
    Nodeptr& Root() {
        
    }
    Nodeptr& Root() const {
        
    }
    void Lrotate(Nodeptr X) {

    }
    void Rrotate(Nodeptr X) {

    }
    static Nodeptr Max(Nodeptr P) {

    }
    static Nodeptr Min(Nodeptr P) {

    }
    Nodeptr Ubound(const key_type& Kv) const {

    }
    Nodeptr Buynode(Nodeptr Parg, char Carg) {

    }
    void Consval(Tptr P, const value_type& V) {

    }
    void Destval(Tptr P) {

    }
    void Freenode(Nodeptr S) {

    }

    Nodeptr     Head;
    size_type   Size;

};



} //namespace ft

#endif