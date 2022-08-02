
#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "ft_iterator.hpp"

#include <iostream>
#include <cstddef>
#include <limits>

namespace ft	{

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



//--------------------
//----map_iterator----
//--------------------
template<class Key, class T, class Compare, typename map_node>
class map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, ft::pair<const Key, T> > {

template< typename k, typename t, typename c, typename a>
friend class map;

public:

    typedef	Compare										                                            key_compare;
    typedef typename ft::iterator<ft::bidirectional_iterator_tag, ft::pair<const Key, T> >			iterator;
    typedef typename iterator::value_type										                    value_type;
    typedef typename iterator::difference_type									                    difference_type;
    typedef typename iterator::reference										                    reference;
    typedef typename iterator::pointer											                    pointer;

    map_iterator(map_node* ptr = NULL, map_node* dumbNode = NULL, const key_compare& comp = key_compare()) :	
        ptr(ptr),
        btreeDumdNode(dumbNode),
        comp(comp) {
    }

    map_iterator(const map_iterator<Key, T, Compare, map_node>& itSrc) : 
        ptr(itSrc.getPtr()),
        btreeDumdNode(itSrc.getDumbNode()),
        comp(itSrc.getComp()) {
    }

    ~map_iterator(void) {}

    map_iterator& operator=(const map_iterator& src) {
        if (*this != src)	{
            ptr = src.getPtr();
            btreeDumdNode = src.getDumbNode();
            comp = src.getComp();
        }
        return (*this);
    }

    map_iterator& operator++(void) {
        if (ptr == btreeDumdNode) {
            ptr = btreeDumdNode->left;
        } else if (isLastNode(ptr) == true) {
            ptr = btreeDumdNode;
        } else if (isLeaf(ptr) == true)	{
            if (ptr == ptr->parent->left) {
                ptr = ptr->parent;
            } else {
                getNextBranch();
            }
        } else {
            if (ptr->right != NULL) {
                ptr = getFarLeft(ptr->right);
            } else {
                getNextBranch();
            }
        }
        return *this;
    }

    map_iterator operator++(int) {
        map_iterator tmp(*this);
        operator++();
        return tmp;
    }

    map_iterator& operator--(void) {
        if (ptr == btreeDumdNode) {
            ptr = btreeDumdNode->right;
        } else if (isFirstNode(ptr) == true) {
            ptr = btreeDumdNode;
        } else if (isLeaf(ptr) == true)	{
            if (ptr == ptr->parent->right) {
                ptr = ptr->parent;
            } else {
                getPreviousBranch();
            }
        } else {
            if (ptr->left != NULL) {
                ptr = getFarRight(ptr->left);
            } else {
                getPreviousBranch();
            }
        }
        return *this;
    }

    map_iterator operator--(int) {
        map_iterator tmp(*this);
        operator--();
        return tmp;
    }


    bool operator==(const map_iterator<Key, T, Compare, map_node>& rhs) const {
        return ptr==rhs.getPtr(); 
    }

    bool operator!=(const map_iterator<Key, T, Compare, map_node>& rhs) const { 
        return ptr!=rhs.getPtr(); 
    }

    pointer operator->() const { 
        return (&ptr->item); 
    }

    reference operator*() const { 
        return (ptr->item); 
    }

private:
    map_node*			ptr;
    map_node*			btreeDumdNode;
    Compare				comp;

	map_node* getDumbNode() const { 
		return (btreeDumdNode);	
	}

	Compare getComp() const {
		return (comp);	
	}

	map_node* getPtr() const {
		return (ptr);
	}

	map_node* getPosParent() const{
        if (ptr != NULL) {
            return (ptr->parent);
		}
        return (NULL);
    }


    void getNextBranch() {
        Key				startKey = ptr->item.first;
        map_node*		cursor = ptr->parent;

        while (cursor != NULL && comp(cursor->item.first, startKey) == true) {
            cursor = cursor->parent;
		}
        ptr = cursor;
    }

    void getPreviousBranch() {
        Key				startKey = ptr->item.first;
        map_node*		cursor = ptr->parent;

        while (cursor != NULL && comp(startKey, cursor->item.first) == true) {
            cursor = cursor->parent;
		}
        ptr = cursor;
    }

    static	map_node* getFarLeft( map_node* cursor ) {
        while (cursor != NULL && cursor->left != NULL) {
            cursor = cursor->left;
		}
        return (cursor);
    }

    static	map_node* getFarRight( map_node* cursor ) {
        while (cursor != NULL && cursor->right != NULL) {
            cursor = cursor->right;
		}
        return (cursor);
    }

    bool isFirstNode( map_node* p )	{
        return (p == btreeDumdNode->left);
    }

    bool isLastNode( map_node* p )	{
        return (p == btreeDumdNode->right);
    }

    static	bool isLeaf(map_node* node)	{
        return (node->left == NULL && node->right == NULL);
    }
}; 




template< typename T>
class map_node	{
public:
	map_node( const T& itemSrc ) :	
		item(itemSrc),
		left(NULL),
		parent(NULL),
		right(NULL) {	
	}

	~map_node() {
	}

	T				item;
	map_node*		left;
	map_node*		parent;
	map_node*		right;
	bool			color;
};


template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::map_node<ft::pair<const Key, T> > > >
class map {

public:

	typedef Key										key_type;
	typedef T										mapped_type;
	typedef ft::pair<const key_type, mapped_type>	value_type;
	typedef	Compare									key_compare;

	typedef size_t									size_type;
	typedef std::ptrdiff_t							difference_type;

	typedef Allocator								allocator_type;
	typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference		const_reference;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;

	typedef typename ft::map_iterator<Key, T, Compare, ft::map_node<value_type> >	iterator;

	typedef typename ft::reverse_iterator<map_iterator<Key, T, Compare, ft::map_node<value_type> > > reverse_iterator;

private:

	typedef typename ft::map_node<value_type>		node_type;


public:

	class value_compare	{
		friend class map<Key, T, Compare, Allocator>;
		public:
			typedef	bool		result_type;
			typedef	value_type	first_argument_type;
			typedef	value_type	second_argument_type;

			bool
			operator()( const value_type& lhs, const value_type& rhs ) const {
				return (comp(lhs.first, rhs.first));
			}

		protected:
			value_compare(Compare c) : comp(c) {}
			Compare	comp;
	};

	
	explicit map(const Compare& comp = key_compare(), const allocator_type & userAlloc = allocator_type()) : 
		head_(NULL),
		dumbNode_(NULL),
		size_(0),
		allocNode_(userAlloc),
		comp(comp) {
		btree_init_dumbNode();
	}

	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& userAlloc = allocator_type()) :
		head_(NULL),
		dumbNode_(NULL),
		size_(0),
		allocNode_(userAlloc),
		comp(comp) {
		insert(first, last);
	}

	map(map const & src) : 
		head_(NULL),
		dumbNode_(NULL),
		size_(0),
		allocNode_(src.allocNode_),
		comp(src.comp) {
		insert(src.begin(), src.end());
	}

	~map() {
		clear();
	}



protected:
	node_type*				head_;
	node_type*				dumbNode_; // allow to point to element after last.
	size_type				size_;
	allocator_type		 	allocNode_;
	const Compare			comp;

/******************************************************************************.
.******************************************************************************.
.*********** 🚧  DEBUG 🚧             ******************************************.
.******************************************************************************.
.******************************************************************************/

private:
// public:
	void debugPrintTree() {
		std::cout << "***********************************" << std::endl;
		std::cout << __func__ << "head_ is pointing to:  " << head_ << std::endl;
		std::cout << "dumbNode_ is... : " << std::endl;
		debugPrintNode(dumbNode_);
		std::cout << "Printing tree of size  " << size_ << std::endl;

		std::cout << "****************ITERATORES*******************" << std::endl;
		iterator it = begin();
		iterator ite = end();

		for(; it != ite; ++it)	{
			debugPrintNode(it.getPtr());
		}
		std::cout << "***********************************" << std::endl;
	}

	static void debugPrintNode(node_type* node)	{
		if (node != NULL)	{
			std::cout << std::endl;
			std::cout << __func__ << std::endl;
			std::cout << "NODE   " << node << std::endl;
			std::cout << "--- KEY    " << node->item.first << std::endl;
			std::cout << "--  VAL    " << node->item.second << std::endl;
			std::cout << "parent " << node->parent;
			if (node->parent != NULL)
				std::cout << "(" << node->parent->item.first << ";" << node->parent->item.second << ")" << std::endl;
			else
				std::cout << "--> THIS NODE IS head_" << std::endl;

			std::cout << " left   " << node->left;
			if (node->left != NULL)
				std::cout << "(" << node->left->item.first << ";" << node->left->item.second << ")";
			std::cout << std::endl;
			std::cout << " right  " << node->right;
			if (node->right != NULL)
				std::cout << "(" << node->right->item.first << ";" << node->right->item.second << ")";
			std::cout << std::endl;
			std::cout << std::endl;
		}
		else
			std::cout << __func__ << "Called with null" << std::endl;
	}


public:

	bool empty() const {
		return size_ == 0; 
	}

	size_type size() const {
		return size_; 
	}

	size_type max_size() const {
		return this->allocNode_.max_size(); 
	}

	iterator begin( void ) 			{
		if (empty() == false && dumbNode_ != NULL) {
			return (iterator(dumbNode_->left, dumbNode_, comp));
		}
		return (iterator(dumbNode_, dumbNode_, comp));
	}

	// const_iterator
	// begin( void ) const		{
	// 	if (empty() == false && dumbNode_ != NULL)
	// 		return (const_iterator(dumbNode_->left, dumbNode_, comp));
	// 	return (const_iterator(dumbNode_, dumbNode_, comp));
	// }

	iterator end() {
		return iterator(dumbNode_, dumbNode_, comp);
	}

	// const_iterator
	// end( void ) const 		{
	// 	return (const_iterator(dumbNode_, dumbNode_, comp));
	// }

	reverse_iterator rbegin() {
		return reverse_iterator(end());
	}
	// const_reverse_iterator	rbegin( void ) 	const	{	return const_reverse_iterator(end()); }
	
	reverse_iterator rend() {
		return reverse_iterator(begin()); 
	}
	// const_reverse_iterator	rend( void ) 	const	{	return const_reverse_iterator(begin()); }

	iterator find (const key_type& k) {
		if (empty() == true) {
			return iterator();
		}
		node_type*	nodeFound = locateNode(head_, k);
		if (nodeFound == NULL) {
			return end();
		}
		return iterator(nodeFound, dumbNode_, comp);
	}

	// const_iterator
	// find (const key_type& k) const	{

	// 	if (empty() == true)
	// 		return(const_iterator());
	// 	node_type* const	nodeFound = locateNode(head_, k);
	// 	if (nodeFound == NULL)
	// 		return (end());
	// 	return (const_iterator(nodeFound, dumbNode_, comp));
	// }

	size_type count (const key_type& k) const {
		return (find(k) != end() ? 1 : 0);
	}

	iterator lower_bound (const key_type& k) {
		if (empty() == true) {
			return iterator();
		}

		node_type* const nodeFound = locateBound(head_, k, isLowerBoundNode);

		if (nodeFound == NULL) {
			return end(); 
		} else {
			return iterator(nodeFound, dumbNode_, comp);
		}
	}

	// const_iterator
	// lower_bound (const key_type& k) const	{

	// 	if (empty() == true)
	// 		return(const_iterator());

	// 	node_type* const	nodeFound = locateBound(head_, k, isLowerBoundNode);

	// 	if (nodeFound == NULL)
	// 		return (end());
	// 	else
	// 		return (const_iterator(nodeFound, dumbNode_, comp));
	// }


	iterator upper_bound (const key_type& k) {

		if (empty() == true) {
			return iterator();
		}

		node_type* const nodeFound = locateBound(head_, k, isUpperBoundNode);

		if (nodeFound == NULL) {
			return end();
		} else {
			return iterator(nodeFound, dumbNode_, comp);
		}
	}

	// const_iterator
	// upper_bound (const key_type& k) const	{

	// 	if (empty() == true)
	// 		return(const_iterator());

	// 	node_type* const	nodeFound = locateBound(head_, k, isUpperBoundNode);

	// 	if (nodeFound == NULL)
	// 		return (end());
	// 	else
	// 		return (const_iterator(nodeFound, dumbNode_, comp));
	// }


	ft::pair<iterator,iterator> equal_range (const key_type& k)	{
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}

	// ft::pair<const_iterator, const_iterator>
	// equal_range (const key_type& k) const	{

	// 	return (ft::make_pair(lower_bound(k), upper_bound(k)));
	// }


	ft::pair<iterator, bool> insert(const value_type& val) {
		return(btree_insert_data(NULL, &head_, val));
	}

	iterator insert (iterator position, const value_type& val)	{
		node_type*	posPtr = position.getPtr();
		if (posPtr == NULL) {
			return (iterator());
		}
		if (position != end() && lower_bound(val.first) == position) {
			return btree_insert_data(posPtr->parent, &posPtr, val).first;
		} else {
			return btree_insert_data(NULL, &head_, val).first;
		}
	}

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last) {
		for (; first != last; first++)
			insert(*first);
	}

	void erase( iterator position )	{
		node_type*	deadNode = position.getPtr();
		node_type*	deadNodeLeft = deadNode->left;
		node_type*	deadNodeRight = deadNode->right;
		node_type*	singleChild = getSingleChild(deadNode);

		if (deadNode == NULL) {
			return;
		}
		if (isLeaf(deadNode) == true) {
			detachFromParent(deadNode);
		} else if (singleChild != NULL) {
			detachFromParent(deadNode, singleChild);
		} else {
			detachFromParent(deadNode, deadNodeLeft);
			node_type*	farRight = getFarRight(deadNodeLeft);
			deadNodeRight->parent = farRight;
			farRight->right = deadNodeRight;
		}
		decSize();
		btree_update_dumbNode();
		freeNode(deadNode);
	}

	size_type erase(const key_type& k) {
		node_type*	target = btree_search_key(head_, k);
		if (target == NULL) {
			return 0;
		} else {
			erase(iterator(target, dumbNode_, comp));
			return 1;
		}
	}

	void erase (iterator first, iterator last)	{
		iterator next;
		while (first != last) {
			next = first;
			next++;
			erase(first);
			first = next;
		}
	}

	void swap (map& src) {
		if (this->head_ != src.head_)	{
			node_type* tmp_head = src.head_;
			node_type* tmp_dumbNode = src.dumbNode_;
			size_t tmp_size = src.size_;
			allocator_type tmp_allocNode = src.allocNode_;

			src.head_ = this->head_;
			src.dumbNode_ = this->dumbNode_;
			src.size_ = this->size_;
			src.allocNode_ = this->allocNode_;

			this->head_ = tmp_head;
			this->dumbNode_ = tmp_dumbNode;
			this->size_ = tmp_size;
			this->allocNode_ = tmp_allocNode;
		}
	}

	map& operator= (const map& src)	{

		if (this->head_ != src.head_) {
			clear();
			if (src.empty() == false) {
				if (src.size() > 2)	{
					iterator half = src.begin();
					for (size_t i = 0; i < src.size() / 2; i++) {
						half++;
					}
					insert(*half);
				}
				insert(src.begin(), src.end());
			}
		}
		return *this;
	}

	mapped_type& operator[]( const key_type& key ) {
		value_type insertValue(key, mapped_type());
		ft::pair<iterator, bool> ret = insert(insertValue);
		return ret.first->second;
	}

	void clear() {
		freeAllNodes(head_);
		freeNode(dumbNode_);
		size_ = 0;
		head_ = NULL;
		dumbNode_ = NULL;
	}

	value_compare value_comp() const {
		return value_compare(comp); 
	}

	key_compare key_comp() const {
		return key_compare(comp);
	}



/////////////////////////////vot tut ostanovilsya
private:
	void detachFromParent(node_type* node, node_type* newChild = NULL)	{
		node_type* parent = node->parent;
		if (parent != NULL)	{
			if (parent->left == node) {
				parent->left = newChild;
			} else if (parent->right == node) {
				parent->right = newChild;
			}
		}
		else if (node == head_) {
			head_ = newChild;
		}
		if (newChild != NULL) {
			newChild->parent = parent;
		}
		node->parent = NULL;
	}

	static node_type* getSingleChild( node_type* node )	{

		if (node->right != NULL && node->left == NULL) {
			return (node->right);
		} else if (node->right == NULL && node->left != NULL) {
			return (node->left);
		} else {
			return (NULL);
		}
	}

	node_type* locateBound( node_type* root, const key_type& key, bool (*isBound)(node_type*, const key_type&) ) const {
		if (root == head_ && isBound(dumbNode_->left, key) == true) {
			return (dumbNode_->left);
		} else if (root == head_ && isBound(dumbNode_->right, key) == false) {
			return (NULL);
		}

		node_type* candidate = root;
		node_type* bestCandidate = NULL;
		while (candidate != NULL)	{
			if (isBound(candidate, key) == true)	{
				bestCandidate = candidate;
				candidate = candidate->left;
			} else {
				candidate = candidate->right;
			}
		}
		return bestCandidate;
	}

	node_type* locateNode( node_type* root, const key_type& key ) const	{

		if (root != NULL)	{
			if (comp(key, root->item.first) == true) {
				return locateNode(root->left, key);
			} else if (isEqualKey(key, root->item.first) == false) {
				return locateNode(root->right, key);
			} else {
				return root;
			}
		} else {
			return NULL;
		}
	}

	static bool isLowerBoundNode( node_type* node, const key_type& key ) {

	typename ft::map<Key, T, Compare> tmpObj;
	typename ft::map<Key, T, Compare>::key_compare cmpFunc = tmpObj.key_comp();

		return (node != NULL
			&& (cmpFunc(node->item.first, key) == false
				|| isEqualKey(node->item.first, key) == true));
	}

	static bool isUpperBoundNode( node_type* node, const key_type& key ) {
		typename ft::map<Key, T, Compare> tmpObj;
		typename ft::map<Key, T, Compare>::key_compare cmpFunc = tmpObj.key_comp();
		return (node != NULL && cmpFunc(key, node->item.first) == true);
	}

	void btree_update_dumbNode()	{
		if (dumbNode_ == NULL) {
			btree_init_dumbNode();
		}
		if (empty() == true)	{
			dumbNode_->left = head_;
			dumbNode_->right = head_;
		} else {
			dumbNode_->left = getFarLeft(head_);
			dumbNode_->right = getFarRight(head_);
		}
	}

	void btree_init_dumbNode() {
		if (dumbNode_ == NULL)	{
			dumbNode_ = allocNode_.allocate(1);
			allocNode_.construct(dumbNode_, node_type(value_type()));
			dumbNode_->left = head_;
			dumbNode_->right = head_;
		}
	}

	node_type* btree_create_node(node_type* parent, key_type k, mapped_type val) {
		node_type*	newNode = allocNode_.allocate(1);
		allocNode_.construct(newNode, node_type(value_type(k ,val)));
		newNode->parent = parent;
		return newNode;
	}


	ft::pair<iterator, bool> btree_insert_data(node_type* parent, node_type **root, value_type pairSrc)	{

		if (*root != NULL)	{
			node_type* tree = *root;
			if (comp(pairSrc.first, tree->item.first) == true) {
				return (btree_insert_data(tree, &tree->left, pairSrc));
			} else if (isEqualKey(pairSrc.first, tree->item.first) == false) {
				return (btree_insert_data(tree, &tree->right, pairSrc));
			} else {
				return ft::pair<iterator, bool>(iterator(*root, dumbNode_, comp), false);
			}
		} else {
			*root = btree_create_node(parent, pairSrc.first, pairSrc.second);
			incSize();
			btree_update_dumbNode();
			return ft::pair<iterator, bool>(iterator(*root, dumbNode_, comp), true);
		}
	}

	node_type* btree_search_key(node_type* root, const key_type& targetKey)	{

		if (root != NULL)	{
			if (comp(targetKey, root->item.first) == true) {
				return (btree_search_key(root->left, targetKey));
			} else if (comp(root->item.first, targetKey) == true) {
				return (btree_search_key(root->right, targetKey));
			}
		}
		return (root);
	}

	static node_type* getFarLeft( node_type* cursor )  {
		while (cursor != NULL && cursor->left != NULL) {
			cursor = cursor->left;
		}
		return cursor;
	}

	static node_type* getFarRight( node_type* cursor ) {
		while (cursor != NULL && cursor->right != NULL) {
			cursor = cursor->right;
		}
		return cursor;
	}

	static bool isLeaf(node_type* node)  {
		return node->left == NULL && node->right == NULL;
	}

	static bool isEqualKey(const Key& existingKey, const Key& newKey) {
		typename ft::map<Key, T, Compare> tmpObj;
		typename ft::map<Key, T, Compare>::key_compare cmpFunc = tmpObj.key_comp();
		return cmpFunc(existingKey, newKey) == false && cmpFunc(newKey, existingKey) == false;
	}

	size_t incSize(size_t inc = 1) {
		size_ += inc; 
		return size_; 
	}

	size_t decSize(size_t inc = 1) {
		size_ -= inc; 
		return size_; 
	}

	void freeNode( node_type* node)	{
		if (node != NULL)	{
			allocNode_.destroy(node);
			allocNode_.deallocate(node, 1);
		}
	}

	void freeAllNodes( node_type* root ) {
		if (root == NULL) {
			return;
		}
		freeAllNodes(root->left);
		freeAllNodes(root->right);
		freeNode(root);
	}

	allocator_type get_allocator() const {
		return allocNode_();
	}

};

template <class Key, class T, class Compare, class Alloc>
void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
	x.swap(y);
};

template< class Key, class T, class Compare, class Alloc >
bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )	{

	if (lhs.size() != rhs.size()) {
		return false;
	}

	typename ft::map<Key,T,Compare,Alloc>::const_iterator lhs_it = lhs.begin();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator rhs_it = rhs.begin();

	for (;lhs_it != lhs.end() && rhs_it != rhs.end(); lhs_it++, rhs_it++) {
		if (lhs_it->first != rhs_it->first || lhs_it->second != rhs_it->second) {
			return false;
		}
	}
	if (lhs_it != lhs.end() || rhs_it != rhs.end()) {
		return false;
	}
	return true;
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
	return !(lhs == rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
	return !(lhs < rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
	return (lhs < rhs || lhs == rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
	return !(lhs <= rhs);
}

} // namespace ft

#endif