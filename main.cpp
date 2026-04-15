#include <iostream>
#include "BST.h"

int main() {
    BST<int, int> tree;

    //empty, clear
    std::cout << "Empty: " << tree.empty() << "\n";
    tree.clear(); 
    std::cout << "Still empty: " << tree.empty() << "\n";

    //Insert
    std::cout << "Insert 10: " << tree.insert(1, 10) << "\n";
    std::cout << "Empty: " << tree.empty() << "\n";
    tree.clear();
    std::cout << "Clear tree" << std::endl;
    std::cout << "Still empty: " << tree.empty() << "\n";

    return 0;
}