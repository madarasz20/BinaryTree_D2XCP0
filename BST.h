#ifndef BST_H
#define BST_H

#include <cstddef>
#include <iterator>
#include <ostream>

template<typename Key, typename Value>
class BST;

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const BST<Key, Value>& tree);

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

		NodeStack(const NodeStack& other);
		NodeStack& operator=(const NodeStack& other);

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

	//copy 
	static Node* clone(Node* node);

public:
	class KeyNotFoundException {};

	friend std::ostream& operator<< <>(std::ostream& os, const BST<Key, Value>& tree);

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

		reference operator*() const;
		Iterator& operator++();
		Iterator operator++(int);

		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
	};

	BST();
	BST(const BST& other);
	BST(BST&& other) noexcept;
	BST& operator=(const BST& other);
	BST& operator=(BST&& other) noexcept;
	~BST();

	bool empty() const;
	void clear();
	bool insert(const Key& k, const Value& val);
	bool contains(const Key& k) const;
	bool remove(const Key& k);

	Value& operator[](const Key& key);
	const Value& operator[](const Key& key) const;

	//iterárot osztály inorder bejáráshoz
	Iterator begin();
	Iterator end();

	Iterator begin() const;
	Iterator end() const;

};

#include "BST.tpp"
#endif // !BST_H
