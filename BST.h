#pragma once

#include<memory>

template<typename Key, typename Value>
class BST {
public:
	BST();

private:
	struct Node
	{
		Key key;
		Value value;
		Node* right;
		Node* left;

		Node(const Key& k, const Value& val)
	};

	Node* root;

	static void clear(Node* node);
};