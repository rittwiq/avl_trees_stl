#include "Node.h"
template<typename T>
Node<T>::Node(T val){
	_value = val;
}
template<typename T>
Node<T>* Node<T>::get_parent(){
	return _parent;
}
template<typename T>
Node<T>* Node<T>::get_left_child(){
	return _left;
}
template<typename T>
Node<T>* Node<T>::get_right_child(){
	return _right;
}
template<typename T>
T Node<T>::get_value(){
	return _value;
}
template<typename T>
void Node<T>::set_parent(Node* parent){
	_parent = parent;
}
template<typename T>
void Node<T>::set_left_child(Node* left){
	_left = left;
}
template<typename T>
void Node<T>::set_right_child(Node* right){
	_right = right;
}
template<typename T>
void Node<T>::set_value(T value){
	_value = value;
}

/*template<typename T>
std::ostream& operator<<(std::ostream& os,Node& n) {
	return os<<n.get_value();
}*/

