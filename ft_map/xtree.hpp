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

template <typename Tr>
class Tree : public Tree_val<Tr> {
public:
    typedef Tree<Tr>        Mytree;
    typedef Tree_val<Tr>    Mybase;
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
        rebind::<Node>::other::pointer              Nodeptr;
    typedef typename allocator_type::template
        rebind::<Nodeptr>::other::reference         Nodepref;
    typedef typename allocator_type::template
        rebind::<key_type>::other::const_reference  Keyref;
    typedef typename allocator_type::template
        rebind::<char>::other::reference            Charref;
    typedef typename allocator_type::template
        rebind::<value_type>::other::reference      Vref;

    static Charref Color(Nodeptr P) {
        return ((Charref)(*P).Color);
    }
    static Charref Isnil(Nodeptr P) {
        return ((Charref)(*P).Isnil);
    }
    static Keyref Key(Nodeptr P) {
        return (Kfn()(Value(P)));
    }
       
}
};



} //namespace ft

#endif