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

template<typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::findNode(Node* node, const Key& key) const {
    while (node != nullptr) {
        if (key < node->key) {
            node = node->leftchild;
        }
        else if (node->key < key) {
            node = node->rightchild;
        }
        else {
            return node;
        }
    }

    return nullptr;
}

template<typename Key, typename Value>
bool BST<Key, Value>::contains(const Key& key) const {
    return findNode(root, key) != nullptr;
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::findMin(Node* node) {
    while (node->leftchild != nullptr) {
        node = node->leftchild;
    }
    return node;
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node*
BST<Key, Value>::removeNode(Node* node, const Key& key, bool& removed) {

    if (node == nullptr) {
        return nullptr;
    }

    if (key < node->key) {
        node->leftchild = removeNode(node->leftchild, key, removed);
    }
    else if (node->key < key) {
        node->rightchild = removeNode(node->rightchild, key, removed);
    }
    else {
        removed = true;

        if (node->leftchild == nullptr && node->rightchild == nullptr) {
            delete node;
            return nullptr;
        }

        if (node->leftchild == nullptr) {
            Node* temp = node->rightchild;
            delete node;
            return temp;
        }

        if (node->rightchild == nullptr) {
            Node* temp = node->leftchild;
            delete node;
            return temp;
        }

        Node* minNode = findMin(node->rightchild);

        node->key = minNode->key;
        node->value = minNode->value;

        node->rightchild = removeNode(node->rightchild, minNode->key, removed);
    }

    return node;
}

template<typename Key, typename Value>
bool BST<Key, Value>::remove(const Key& key) {
    bool removed = false;
    root = removeNode(root, key, removed);
    return removed;
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node*& BST<Key, Value>::findSlot(const Key& key) {
    Node** current = &root;

    while (*current != nullptr) {
        if (key < (*current)->key) {
            current = &((*current)->leftchild);
        }
        else if ((*current)->key < key) {
            current = &((*current)->rightchild);
        }
        else {
            break;
        }
    }

    return *current;
}

template<typename Key, typename Value>
Value& BST<Key, Value>::operator[](const Key& key) {
    Node*& slot = findSlot(key);

    if (slot == nullptr) {
        slot = new Node(key, Value());
    }

    return slot->value;
}

template<typename Key, typename Value>
const Value& BST<Key, Value>::operator[](const Key& key) const {
    Node* node = findNode(root, key);

    if (node == nullptr) {
        throw KeyNotFoundException();
    }

    return node->value;
}