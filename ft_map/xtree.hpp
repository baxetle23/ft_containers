#ifndef XTREE_H_
#define XTREE_H_

namespace ft {

template<typename Tr>
class Tree_nod : public Tr {
protected:
    typedef typename Tr::allocator_type     allocator_type;
    typedef typename Tr::key_compare        key_compare;
    typedef typename Tr::value_type         value_type;
    typedef typename allocator_type::template
            rebind<void>::other::pointer Genptr;

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



} //namespace ft

#endif