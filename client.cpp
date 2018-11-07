#include "avl.cpp"
#include<algorithm>
using namespace std;
int main() {
	AVL_Tree<int>a;
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.insert(5);
	a.insert(6);
	a.insert(7);
	a.inorder();
	a.preorder();
	cout<<a.get_height()<<"\n";
	a.insert(8);
	a.insert(9);
	a.insert(10);
	a.insert(11);
	a.inorder();
	a.preorder();
	cout<<a.get_height()<<" & " << a.checkTree() <<"\n";
	cout<<"Erasing 8\n";
	a.erase(8);
	a.inorder();
	a.preorder();
	cout<<a.get_height()<<" & " << a.checkTree() <<"\n";
	
	a.inorder();
	a.preorder();
	auto c=a.begin();
	while(c!=a.end()) {
		cout<<*c<<",\t";
		c++;
	}
	cout<<"\n";
	//a.preorder();
	cout<<a.get_height()<<" & " << a.checkTree() <<"\n";
	for_each(a.begin(), a.end(), [](auto itr){ std::cout<<itr<<", ";});
	cout<<"\n";

	auto b=a.rend();
	cout<<*b<<",\t";
	b--;
	cout<<*b<<",\t";
	b--;
	cout<<*b<<",\t";
	b--;
	cout<<*b<<",\t";
	b--;
	cout<<*b<<",\t";
	b--;
	cout<<*b<<",\t";
	b--;
	cout<<*b<<",\t";
	b--;
	cout<<"\n";
	b=a.rend();
	
}
