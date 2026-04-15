#pragma once

template<typename Key, typename Value>
BST<Key, Value>::Node::Node(const Key& k, const Value& val)
    : key(k), value(val), leftchild(nullptr), rightchild(nullptr) {
}

template<typename Key, typename Value>
BST<Key, Value>::BST()
    : root(nullptr) {
}

template<typename Key, typename Value>
BST<Key, Value>::~BST() {
    clear();
}

template<typename Key, typename Value>
void BST<Key, Value>::clear(Node* node) {
    if (node == nullptr) {
        return;
    }

    clear(node->leftchild);
    clear(node->rightchild);
    delete node;
}

template<typename Key, typename Value>
void BST<Key, Value>::clear() {
    clear(root);
    root = nullptr;
}

template<typename Key, typename Value>
bool BST<Key, Value>::empty() const {
    return root == nullptr;
}

template<typename Key, typename Value>
bool BST<Key, Value>::insert(const Key& key, const Value& value) {
    if (root == nullptr) {
        root = new Node(key, value);
        return true;
    }

    Node* current = root;

    while (true) {
        if (key < current->key) {
            if (current->leftchild == nullptr) {
                current->leftchild = new Node(key, value);
                return true;
            }
            current = current->leftchild;
        }
        else if (current->key < key) {
            if (current->rightchild == nullptr) {
                current->rightchild = new Node(key, value);
                return true;
            }
            current = current->rightchild;
        }
        else {
            return false;
        }
    }
}