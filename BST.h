#ifndef BST_H
#define BST_H

template<typename Key, typename Value>
class BST {
private:
	struct Node
	{
		Key key;
		Value value;
		Node* rightchild;
		Node* leftchild;

		Node(const Key& k, const Value& val);
	};

	Node* root;

	static void clear(Node* node);
public:
	BST();
	~BST();

	bool empty() const;
	void clear();
	bool insert(const Key& k, const Value& val);
	//bool remove(const Key k);
	//bool contains(const Key k);

	//iterárot osztály inorder bejáráshoz


};

#include "BST.tpp"
#endif // !BST_H
