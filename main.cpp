#include <iostream>
#include "BST.h"

int main() {
    BST<int, int> tree;

    //empty, clear
    std::cout << "Empty and clear:" << "\n";
    std::cout << "\tEmpty: " << (tree.empty() ? "yes" : "no") << "\n";
    tree.clear(); 
    std::cout << "\tStill empty: " << (tree.empty() ? "yes" : "no") << "\n";

    //Insert
    std::cout << "Insert:" << "\n";
    std::cout << "\tInsert 10 with key 1: " << tree.insert(1, 10) << "\n";
    std::cout << "\tEmpty: " << tree.empty() << "\n";
    tree.clear();
    std::cout << "\tCleared tree" << std::endl;
    std::cout << "\tStill empty: " << tree.empty() << "\n";

    //contains
    std::cout << "Contains:" << "\n";
    std::cout << "\tContains key 1?: " << (tree.contains(1) ? "true" : "false") << "\n";

    //remove
    std::cout << "Remove:" << "\n";
    std::cout << "\tInsert 50 with key 2: " << tree.insert(2, 50) << "\n";
    std::cout << "\tInsert 24 with key 3: " << tree.insert(3, 24) << "\n";
    std::cout << "\tInsert 60 with key 4: " << tree.insert(4, 60) << "\n";
    std::cout << "\tInsert 12 with key 5: " << tree.insert(5, 12) << "\n";
    std::cout << "\tInsert 58 with key 6: " << tree.insert(6, 58) << "\n";
    std::cout << "\tInsert 16 with key 7: " << tree.insert(7, 16) << "\n";

    std::cout << "\tRemove 12: " << (tree.remove(5) ? "value removed" : "value could not be removed") << "\n";
    //mi a 24-nek a baloldali gyereke kene
    std::cout << "\tContains 12?: " << (tree.contains(5) ? "true" : "false") << "\n";

    //operator
    std::cout << "Operator []:" << "\n";
    tree[8] = 71;
    tree[9] = 68;
    tree[10] = 82;
    try
    {
        std::cout << "\ttree[8] : " << tree[8] << "\n";
        std::cout << "\ttree[9] : " << tree[9] << "\n";

        //uj kulcs letrehoz
        std::cout << "\ttree[20] = " << (tree[20] ? "Node exsists with given key " : "There is no Node with given key") << "\n";
    }
    catch (const BST<int, int>::KeyNotFoundException&)
    {
        std::cout << "\tKey not found exception caught\n";
    }

    std::cout << "Inorder traversal:\n";

    for (auto item : tree) {
        std::cout << "\t" << item.key << " -> " << item.value << "\n";
    }

    BST<int, int> tree2;

    tree2.insert(10, 100);
    tree2.insert(5, 50);
    tree2.insert(15, 150);
    tree2.insert(3, 30);
    tree2.insert(7, 70);

    std::cout << "Tree: " << tree2 << "\n";

    const BST<int, int>& constTree = tree2;
    std::cout << "Const tree: " << constTree << "\n";
    
    return 0;
}