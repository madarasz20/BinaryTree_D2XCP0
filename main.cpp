#include <iostream>
#include "BST.h"

int main() {
    BST<int, int> tree;

    std::cout << "Empty: " << tree.empty() << "\n";

    tree.clear(); 

    std::cout << "Still empty: " << tree.empty() << "\n";

    return 0;
}