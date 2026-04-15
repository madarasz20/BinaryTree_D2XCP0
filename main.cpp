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
    /*    tree.clear();
    std::cout << "Clear tree" << std::endl;
    std::cout << "Still empty: " << tree.empty() << "\n";*/

    //contains
    std::cout << "Contains key 1?: " << (tree.contains(1) ? "true" : "false") << "\n";

    return 0;
}