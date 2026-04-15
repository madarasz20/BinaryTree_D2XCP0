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
    std::cout << "Cleared tree" << std::endl;
    std::cout << "Still empty: " << tree.empty() << "\n";

    //contains
    std::cout << "Contains key 1?: " << (tree.contains(1) ? "true" : "false") << "\n";

    //remove
    std::cout << "Insert 50 with key 2: " << tree.insert(2, 50) << "\n";
    std::cout << "Insert 24 with key 3: " << tree.insert(3, 24) << "\n";
    std::cout << "Insert 60 with key 4: " << tree.insert(4, 60) << "\n";
    std::cout << "Insert 12 with key 5: " << tree.insert(5, 12) << "\n";
    std::cout << "Insert 58 with key 6: " << tree.insert(6, 58) << "\n";
    std::cout << "Insert 16 with key 7: " << tree.insert(7, 16) << "\n";

    std::cout << "Remove 12: " << (tree.remove(5) ? "value removed" : "value could not be removed") << "\n";
    //mi a 24-nek a baloldali gyereke kene
    std::cout << "Contains 12?: " << (tree.contains(5) ? "true" : "false") << "\n";


    return 0;
}