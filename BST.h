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

	class NodeStack {
	private:
		struct StackNode {
			Node* data;
			StackNode* next;

			StackNode(Node* d, StackNode* n);
		};

		StackNode* topNode;

	public:
		NodeStack();
		~NodeStack();

		NodeStack(const NodeStack&) = delete;
		NodeStack& operator=(const NodeStack&) = delete;

		bool empty() const;
		void push(Node* node);
		void pop();
		Node* top() const;
		void clear();
	};

	Node* root;

	static void clear(Node* node);
	Node* findNode(Node* node, const Key& key) const;
	//removehelper
	Node* removeNode(Node* node, const Key& key, bool& removed);
	Node* findMin(Node* node);

	Node*& findSlot(const Key& key);

public:
	class KeyNotFoundException {};

	BST();
	~BST();

	bool empty() const;
	void clear();
	bool insert(const Key& k, const Value& val);
	bool contains(const Key& k) const;
	bool remove(const Key& k);

	Value& operator[](const Key& key);
	const Value& operator[](const Key& key) const;

	//iterárot osztály inorder bejáráshoz


};

#include "BST.tpp"
#endif // !BST_H
