#include<iostream>
template<typename T>
class Node{
	private:
		Node* _parent=nullptr;
		Node* _left=nullptr;
		Node* _right=nullptr;
		T _value;
	public:
		bool right_thread=false;
		bool left_thread=false;
		Node(T);
		Node* get_parent();
		Node* get_left_child();
		Node* get_right_child();
		T get_value();
		void set_parent(Node* parent);
		void set_left_child(Node* left);
		void set_right_child(Node* right);
		void set_value(T);
};
