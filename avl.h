#include "Node.cpp"
#include<functional>
#define ABS(a) a>0?a:-a;
template<typename Key, typename Compare = std::less<Key>>
class AVL_Tree {
	private:
		Node<Key> *root=nullptr;
		int size;
		Node<Key> *insert(Node<Key> *, Node<Key>*);
		void inorder(Node<Key> *);
		void preorder(Node<Key> *);
		int get_height(Node<Key>*);
		int balance_factor(Node<Key>*);
		void left_rotate(Node<Key>*, Node<Key> *);
		void right_rotate(Node<Key> *, Node<Key> *);
		Node<Key> *_find(Node<Key> *,Key);
		Node<Key> *erase(Node<Key> *, Key );
		Node<Key> *leftmost(Node<Key> *itr) {
			while(itr->get_left_child()!=NULL) itr = itr->get_left_child();
			return itr;
		}
		Node<Key> *rightmost(Node<Key> *itr) {
			while(itr->get_right_child()!=NULL) itr = itr->get_right_child();
			return itr;
		}
		Node<Key> *_find(Key);
		bool checkTree(Node<Key> *);
		Node<Key> *copyTree(Node<Key> *, Node<Key> *);
		void deleteTree(Node<Key> *);
	public:
		class Iterator : public std::iterator<std::bidirectional_iterator_tag, Key, long> {
			private:
				Node<Key> *p_;
			public:
				Iterator() : p_(nullptr) {
				}
				Iterator(Node<Key> *p) : p_(p) {
				}
				bool operator==(Iterator it) {
					return p_ == it.p_;
				}
				bool operator!=(Iterator it) {
					return !(this->p_ == it.p_);
				}
				Iterator operator++() {
					if(p_->get_right_child()==nullptr) {	// traverse up till we find that its the left node
						Node<Key> *curr=p_;
						while(curr->get_parent()!=nullptr && curr->get_parent()->get_right_child() == curr)
							curr=curr->get_parent();
						*this=Iterator(curr->get_parent());
						return Iterator(curr->get_parent());
					}
					else {			// as there is a right node traverse to the leftmost node in the right child
						Node<Key> *curr=p_->get_right_child();
						while(curr->get_left_child()!=nullptr)  curr=curr->get_left_child();
						*this=Iterator(curr);
						return Iterator(curr);
					}
				}
				Iterator operator++(int) {
					Iterator temp(*this);
					++*this;
					return temp;
				}
				Iterator operator--() {
					if(p_->get_left_child()==nullptr) {	// traverse up till we find that its the left node
						Node<Key> *curr=p_;
						while(curr->get_parent()!=nullptr && curr->get_parent()->get_left_child() == curr) {
							curr=curr->get_parent();
						}
						*this=Iterator(curr->get_parent());
						return *this;
					}
					else {			// as there is a left node traverse to the rightmost node in the right child
						Node<Key> *curr=p_->get_left_child();
						while(curr->get_right_child()!=nullptr)  curr=curr->get_right_child();
						*this=Iterator(curr);
						return Iterator(curr);
					}
				}
				Iterator operator--(int) {
					Iterator temp(*this);
					--*this;
					return temp;
				}
				Key operator *() {
					return p_->get_value();
				}
		};
		
		// allocation / deallocation
		AVL_Tree();
		AVL_Tree(const AVL_Tree&);
		AVL_Tree(AVL_Tree&&);
		AVL_Tree& operator=(const AVL_Tree&);
		AVL_Tree& operator=(AVL_Tree&&);
		~AVL_Tree();
		
		// Accessors
		
		Iterator begin() {
			return Iterator(leftmost(this->root));
		}
		Iterator end() {
			return nullptr;
		}
		
		
		Iterator rbegin() {
			return Iterator(root);
		}
		Iterator rend() {
			return Iterator(rightmost(this->root));
		}
		bool empty() {
			return begin()==nullptr;
		}
		
		// Modifier
		void insert(Key);
		void erase(Key);
		bool checkTree();
		
		// Operations 
		void inorder();
		void preorder();
		int get_height();
		void replace(Key,Key);
		Iterator find(Key val) {
			return Iterator(_find(val));
		}
};
