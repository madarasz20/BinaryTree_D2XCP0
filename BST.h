#ifndef BST_H
#define BST_H

#include <cstddef>
#include <iterator>

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

	class IteratorValue {
	public:
		const Key& key;
		Value& value;

		IteratorValue(const Key& k, Value& v);
	};

	class Iterator {
	private:
		Node* current;
		NodeStack path;

		void pushLeftBranch(Node* node);
		void advance();

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = IteratorValue;
		using difference_type = std::ptrdiff_t;
		using pointer = void;
		using reference = IteratorValue;

		Iterator();
		explicit Iterator(Node* root);

		reference operator*();
		Iterator& operator++();
		Iterator operator++(int);

		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
	};

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
