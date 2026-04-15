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
	Node* findNode(Node* node, const Key& key) const;

public:
	BST();
	~BST();

	bool empty() const;
	void clear();
	bool insert(const Key& k, const Value& val);
	bool contains(const Key& k) const;
	bool remove(const Key& k);

	//removehelper
	Node* removeNode(Node* node, const Key& key, bool& removed);
	Node* findMin(Node* node);
	

	//iterárot osztály inorder bejáráshoz


};

#include "BST.tpp"
#endif // !BST_H
