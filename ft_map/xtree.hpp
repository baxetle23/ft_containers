#ifndef XTREE_H_
#define XTREE_H_

#include "ft_iterator.hpp"

namespace ft {

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
    typedef typename Tr::Key_compare    key_compare;
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
        rebind<value_type>::other::_const_reference     const_reference;
    
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
        typedef typename Mybase::difference_type                deffirence_type;
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

};



} //namespace ft

#endif