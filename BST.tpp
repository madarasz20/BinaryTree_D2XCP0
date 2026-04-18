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
BST<Key, Value>::BST(const BST& other)
    : root(clone(other.root)) {
}

template<typename Key, typename Value>
BST<Key, Value>::BST(BST&& other) noexcept
    : root(other.root) {
    other.root = nullptr;
}

template<typename Key, typename Value>
BST<Key, Value>::~BST() {
    clear();
}

template<typename Key, typename Value>
BST<Key, Value>& BST<Key, Value>::operator=(const BST& other) {
    if (this != &other) {
        Node* newRoot = clone(other.root);
        clear(root);
        root = newRoot;
    }

    return *this;
}

template<typename Key, typename Value>
BST<Key, Value>& BST<Key, Value>::operator=(BST&& other) noexcept {
    if (this != &other) {
        clear(root);
        root = other.root;
        other.root = nullptr;
    }

    return *this;
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
typename BST<Key, Value>::Node* BST<Key, Value>::clone(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    Node* newNode = new Node(node->key, node->value);
    newNode->leftchild = clone(node->leftchild);
    newNode->rightchild = clone(node->rightchild);

    return newNode;
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

template<typename Key, typename Value>
BST<Key, Value>::NodeStack::StackNode::StackNode(Node* d, StackNode* n)
    : data(d), next(n) {
}

template<typename Key, typename Value>
BST<Key, Value>::NodeStack::NodeStack()
    : topNode(nullptr) {
}

template<typename Key, typename Value>
BST<Key, Value>::NodeStack::~NodeStack() {
    clear();
}

template<typename Key, typename Value>
BST<Key, Value>::NodeStack::NodeStack(const NodeStack& other)
    : topNode(nullptr) {
    if (other.topNode == nullptr) {
        return;
    }

    StackNode* otherCurrent = other.topNode;
    StackNode* newTop = new StackNode(otherCurrent->data, nullptr);
    StackNode* thisCurrent = newTop;
    otherCurrent = otherCurrent->next;

    while (otherCurrent != nullptr) {
        thisCurrent->next = new StackNode(otherCurrent->data, nullptr);
        thisCurrent = thisCurrent->next;
        otherCurrent = otherCurrent->next;
    }

    topNode = newTop;
}

template<typename Key, typename Value>
typename BST<Key, Value>::NodeStack&
BST<Key, Value>::NodeStack::operator=(const NodeStack& other) {
    if (this != &other) {
        clear();

        if (other.topNode == nullptr) {
            topNode = nullptr;
            return *this;
        }

        StackNode* otherCurrent = other.topNode;
        StackNode* newTop = new StackNode(otherCurrent->data, nullptr);
        StackNode* thisCurrent = newTop;
        otherCurrent = otherCurrent->next;

        while (otherCurrent != nullptr) {
            thisCurrent->next = new StackNode(otherCurrent->data, nullptr);
            thisCurrent = thisCurrent->next;
            otherCurrent = otherCurrent->next;
        }

        topNode = newTop;
    }

    return *this;
}

template<typename Key, typename Value>
bool BST<Key, Value>::NodeStack::empty() const {
    return topNode == nullptr;
}

template<typename Key, typename Value>
void BST<Key, Value>::NodeStack::push(Node* node) {
    topNode = new StackNode(node, topNode);
}

template<typename Key, typename Value>
void BST<Key, Value>::NodeStack::pop() {
    if (topNode != nullptr) {
        StackNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }
}

template<typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::NodeStack::top() const {
    return topNode->data;
}

template<typename Key, typename Value>
void BST<Key, Value>::NodeStack::clear() {
    while (!empty()) {
        pop();
    }
}

template<typename Key, typename Value>
BST<Key, Value>::IteratorValue::IteratorValue(const Key& k, Value& v)
    : key(k), value(v) {
}

template<typename Key, typename Value>
BST<Key, Value>::Iterator::Iterator()
    : current(nullptr) {
}

template<typename Key, typename Value>
BST<Key, Value>::Iterator::Iterator(Node* root)
    : current(nullptr) {
    pushLeftBranch(root);
    advance();
}

template<typename Key, typename Value>
void BST<Key, Value>::Iterator::pushLeftBranch(Node* node) {
    while (node != nullptr) {
        path.push(node);
        node = node->leftchild;
    }
}

template<typename Key, typename Value>
void BST<Key, Value>::Iterator::advance() {
    if (path.empty()) {
        current = nullptr;
        return;
    }

    current = path.top();
    path.pop();

    if (current->rightchild != nullptr) {
        pushLeftBranch(current->rightchild);
    }
}

template<typename Key, typename Value>
typename BST<Key, Value>::Iterator::reference BST<Key, Value>::Iterator::operator*() const {
    return IteratorValue(current->key, current->value);
}

template<typename Key, typename Value>
typename BST<Key, Value>::Iterator& BST<Key, Value>::Iterator::operator++() {
    advance();
    return *this;
}

template<typename Key, typename Value>
typename BST<Key, Value>::Iterator BST<Key, Value>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename Key, typename Value>
bool BST<Key, Value>::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

template<typename Key, typename Value>
bool BST<Key, Value>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

template<typename Key, typename Value>
typename BST<Key, Value>::Iterator BST<Key, Value>::begin() {
    return Iterator(root);
}

template<typename Key, typename Value>
typename BST<Key, Value>::Iterator BST<Key, Value>::end() {
    return Iterator();
}

template<typename Key, typename Value>
typename BST<Key, Value>::Iterator BST<Key, Value>::begin() const {
    return Iterator(root);
}

template<typename Key, typename Value>
typename BST<Key, Value>::Iterator BST<Key, Value>::end() const {
    return Iterator();
}

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const BST<Key, Value>& tree) {
    bool first = true;

    for (auto item : tree) {
        if (!first) {
            os << ' ';
        }

        os << item.key << ':' << item.value;
        first = false;
    }

    return os;
}