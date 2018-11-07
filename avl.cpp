#include "avl.h"
#include<iostream>
template<typename Key, typename Compare>
AVL_Tree<Key, Compare>::AVL_Tree() {
}
template<typename Key, typename Compare>
AVL_Tree<Key, Compare>::AVL_Tree(const AVL_Tree& __x) {
	if(__x.root != nullptr)
		this->root=copyTree(nullptr, __x.root);
}
template<typename Key, typename Compare>
AVL_Tree<Key, Compare>::AVL_Tree(AVL_Tree&& __x) {
	if(__x.root != nullptr) {
		this->root=copyTree(nullptr, __x.root);
		deleteTree(__x->root);
	}
}
template<typename Key, typename Compare>
AVL_Tree<Key, Compare>& AVL_Tree<Key, Compare>::operator=(AVL_Tree<Key, Compare> &&rhs) {
	if(this!=&rhs) {
		this->root=copyTree(nullptr, rhs.root);
		deleteTree(rhs.root);
	}
	return *this;
}

template<typename Key, typename Compare>
AVL_Tree<Key, Compare>& AVL_Tree<Key, Compare>::operator=(const AVL_Tree<Key, Compare>& rhs) {
	if(this!=&rhs) {
		deleteTree(this->root);
		this->root=copyTree(nullptr, rhs.root);
	}
	return *this;
}
template<typename Key, typename Compare>
AVL_Tree<Key, Compare>::~AVL_Tree() {
	if(this->root !=nullptr) {
		deleteTree(this->root);
	}
}
template<typename Key, typename Compare>
Node<Key> *AVL_Tree<Key, Compare>::copyTree(Node<Key> *parent, Node<Key> *node) {
	if(node!=nullptr) {
		Node<Key> *tmp=new Node<Key>(node->get_value());
		tmp->set_parent(parent);
		tmp->set_left_child(copyTree(tmp, node->get_left_child()));
		tmp->set_right_child(copyTree(tmp, node->get_right_child()));
		return tmp;
	}
	else
		return nullptr;
}
template<typename Key, typename Compare>
void AVL_Tree<Key, Compare>::deleteTree(Node<Key> *root) {
	if(root!=nullptr) {
		deleteTree(root->get_left_child());
		deleteTree(root->get_right_child());
		delete root;
	}
}

/*
INSERTION
Let the newly inserted node be w
1) Perform standard BST insert for w.
2) Starting from w, travel up and _find the first unbalanced node. Let z be the first unbalanced node, y be the child of z that comes on the path from w to z and x be the grandchild of z that comes on the path from w to z.
3) Re-balance the tree by performing appropriate rotations on the subtree rooted with z. There can be 4 possible cases that needs to be handled as x, y and z can be arranged in 4 ways. Following are the possible 4 arrangements:
a) y is left child of z and x is left child of y (Left Left Case)
b) y is left child of z and x is right child of y (Left Right Case)
c) y is right child of z and x is right child of y (Right Right Case)
d) y is right child of z and x is left child of y (Right Left Case)
Source: http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
*/
template<typename Key, typename Compare>
void AVL_Tree<Key, Compare>::insert(Key k) {
	Node<Key> *w=new Node<Key>(k);
	this->root=insert(this->root, w);
	Node<Key> *z=w, *y=nullptr, *x=nullptr, *m=w->get_parent();
	while(z->get_parent()!=nullptr && balance_factor(z)<2) {
		x=y;
		y=z;
		z=z->get_parent();
		m=z->get_parent();
	}
	if(balance_factor(z) >= 2) {
		if(y==z->get_right_child()) {	// RIGHT
			if(x==y->get_right_child()) { // RIGHT
				/*
					Case #1: Right Right: LEFT ROTATE(Z)
				*/
				left_rotate(z, y);
				
			}
			else {	// LEFT
				/*
					Case #2: RIGHT LEFT : RIGHT ROTATE(Y) -> LEFT ROTATE(Z)
				*/
				right_rotate(y, x);
				left_rotate(z, x);
				
			}
		}
		else {	// LEFT
			if(x==y->get_right_child()) { // RIGHT
				/*
					Case #3: LEFT RIGHT: LEFT ROTATE(Y) -> RIGHT ROTATE(Z)
				*/
				left_rotate(y, x);
				right_rotate(z, x);
			}
			else {	//LEFT
				/*
					Case #4:LEFT LEFT : RIGHT ROTATE(Z)
				*/
				right_rotate(z, y);
			}
		}
	}
}

template<typename Key, typename Compare>
void AVL_Tree<Key, Compare>::left_rotate(Node<Key> *z, Node<Key> *y){
	Node<Key> *m=z->get_parent();
	z->set_right_child(y->get_left_child());
	if(y->get_left_child())
		y->get_left_child()->set_parent(z);
	y->set_left_child(z);
	z->set_parent(y);
	y->set_parent(m);
	if(y->get_parent()==nullptr)
		this->root=y;
	else
		if(m->get_left_child()==z) m->set_left_child(y);
		else  m->set_right_child(y);
	
}
template<typename Key, typename Compare>
void AVL_Tree<Key, Compare>::right_rotate(Node<Key> *z, Node<Key> *y){
	Node<Key> *m=z->get_parent();
	z->set_left_child(y->get_right_child());
	y->set_right_child(z);
	y->set_parent(z->get_parent());
	z->set_parent(y);
	if(y->get_parent()==nullptr)
		this->root=y;
	else
		if(m->get_left_child()==z) m->set_left_child(y);
		else  m->set_right_child(y);
}
template<typename Key, typename Compare>
int AVL_Tree<Key, Compare>::get_height() {
	return get_height(this->root);
}
template<typename Key, typename Compare>
int AVL_Tree<Key, Compare>::get_height(Node<Key> *curr) {
	if(curr==nullptr) 
		return 0;
	int l=get_height(curr->get_left_child())+1;
	int r=get_height(curr->get_right_child())+1;
	return l>r?l:r;
}
template<typename Key, typename Compare>
int AVL_Tree<Key, Compare>::balance_factor(Node<Key>* curr) {
	if(curr==nullptr) return 0;
	return ABS(get_height(curr->get_right_child()) - get_height(curr->get_left_child()));
}
template<typename Key, typename Compare>
Node<Key> *AVL_Tree<Key, Compare>::insert(Node<Key> *curr, Node<Key> *w) {
	if(curr==nullptr) 
		return w;
	if(Compare()(curr->get_value(), w->get_value())) {
		Node<Key> *tmp=insert(curr->get_right_child(), w);
		curr->set_right_child(tmp);
		tmp->set_parent(curr);
	}
	else {
		Node<Key> *tmp=insert(curr->get_left_child(), w);
		curr->set_left_child(tmp);
		tmp->set_parent(curr);
	}
	return curr;
}

template<typename Key, typename Compare>
Node<Key> *AVL_Tree<Key, Compare>::_find( Key val) {
	Node<Key> *tmp=_find(this->root, val);
	return tmp;
}
template<typename Key, typename Compare>
Node<Key> *AVL_Tree<Key, Compare>::_find(Node<Key> *curr, Key val) {
	Node<Key> *tmp=nullptr;
	if(curr==nullptr) 
		return nullptr;
	if(!(Compare()(curr->get_value(), val) || Compare()(val, curr->get_value())))	{
		tmp=curr;
	}
	else if(Compare()(curr->get_value(), val))
		tmp=_find(curr->get_right_child(), val);
	else
		tmp=_find(curr->get_left_child(), val);
	return tmp;
}
template<typename Key, typename Compare>
void AVL_Tree<Key, Compare>::replace( Key val, Key newval) {
	erase(val);
	insert(newval);
}
template<typename Key, typename Compare>
Node<Key> *leftmost(Node<Key> *curr) {
	if(curr==nullptr) return nullptr;
	Node<Key> *tmp=curr;
	while(tmp->get_left_child()!=nullptr)
		tmp=tmp->get_left_child();
	return tmp;
}

template<typename Key, typename Compare>
Node<Key> *AVL_Tree<Key, Compare>::erase(Node<Key> *root, Key k) {
	if(root==nullptr) return root;
	if(Compare()(k , root->get_value())) root->set_left_child(erase(root->get_left_child(), k));
	else if(Compare()(root->get_value(), k)) root->set_right_child(erase(root->get_right_child(), k));
	else {
		if( root->get_left_child()==nullptr || root->get_right_child()==nullptr ) {
			Node<Key> *tmp=root->get_left_child()==nullptr ? root->get_right_child() : root->get_left_child();
			if(tmp==nullptr) {
				tmp=root;
				root=nullptr;
			}
			else {
				tmp->set_parent(root->get_parent());
				root=tmp;
			}
		}
		else {
			Node<Key> *tmp=leftmost(root->get_right_child());
			root->set_value(tmp->get_value());
			root->set_right_child(erase(root->get_right_child(), tmp->get_value()));
		}
	}
	if(root==nullptr) return root;
	Node<Key> *y=nullptr, *x=nullptr, *m=root->get_parent(), *z=root;
	while(z->get_parent()!=nullptr && balance_factor(z)<2) {
		x=y;
		y=z;
		z=z->get_parent();
		m=z->get_parent();
	}
	if(balance_factor(z) >= 2) {
		if(y==z->get_right_child()) {	// RIGHT
			if(x==y->get_right_child()) { // RIGHT
				/*
					Case #1: Right Right: LEFT ROTATE(Z)
				*/
				left_rotate(z, y);
			}
			else {	// LEFT
				/*
					Case #2: RIGHT LEFT : RIGHT ROTATE(Y) -> LEFT ROTATE(Z)
				*/
				right_rotate(y, x);
				left_rotate(z, x);
			}
		}
		else {	// LEFT
			if(x==y->get_right_child()) { // RIGHT
				/*
					Case #3: LEFT RIGHT: LEFT ROTATE(Y) -> RIGHT ROTATE(Z)
				*/
				left_rotate(y, x);
				right_rotate(z, x);
			}
			else {	//LEFT
				/*
					Case #4:LEFT LEFT : RIGHT ROTATE(Z)
				*/
				right_rotate(z, y);
			}
		}
	}
	return root;
}

template<typename Key, typename Compare>
void AVL_Tree<Key, Compare>::erase(Key k) {
	erase( this->root, k);
}

template<typename Key, typename Compare>
void AVL_Tree<Key, Compare>::inorder() {
	inorder(this->root);
	std::cout<<"\n";
}
template<typename Key, typename Compare>
void AVL_Tree<Key, Compare>::inorder(Node<Key> *curr) {
	if(curr!=nullptr) {
		inorder(curr->get_left_child());
		std::cout<<curr->get_value()<<", ";
		inorder(curr->get_right_child());
	}
}


template<typename Key, typename Compare>
bool AVL_Tree<Key, Compare>::checkTree() {
	if(checkTree(this->root))
		std::cout<<"No errors detected\n";
		return true;
	return false;
}
template<typename Key, typename Compare>
bool AVL_Tree<Key, Compare>::checkTree(Node<Key> *curr) {
	if(curr!=nullptr) {
		bool a=checkTree(curr->get_left_child());
		a=a&checkTree(curr->get_right_child());
		if(curr!=this->root)
			a=a&(curr->get_parent()->get_left_child()==curr || curr->get_parent()->get_right_child()==curr);
		if(!a) std::cout<<"Error at "<<curr->get_value()<<"\n";
		return a;
	}
	else return true;
}




template<typename Key, typename Compare>
void AVL_Tree<Key, Compare>::preorder() {
	preorder(this->root);
	std::cout<<"\n";
}
template<typename Key, typename Compare>
void AVL_Tree<Key, Compare>::preorder(Node<Key> *curr) {
	if(curr!=nullptr) {
		std::cout<<curr->get_value()<<", ";
		preorder(curr->get_left_child());
		preorder(curr->get_right_child());
	}
}
