#include "binary.h"
#include <iostream>

int compare(void* d1, void* d2) {
    char c1 = *((char*)d1);
    char c2 = *((char*)d2);

    if (c1 == c2) {
        return 0;
    } else if (c1 > c2) {
        return 1;
    } else {
        return -1;
    }
}

void print(void* data) {
    char c = *((char*)data);
    std::cout << c << " ";
}

void p_order(char *a, int size) {
    for (int i=0; i<size; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int main(void) {
    char pre[] = {'A', 'B', 'D', 'E', 'C', 'F'};
    char mid[] = {'D', 'B', 'E', 'A', 'F', 'C'};
    char pst[] = {'D', 'E', 'B', 'F', 'C', 'A'};
    char lvl[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    char heap[] = {'A', 'B', 'C', 'D', 'E', ' ', 'F'};
    char bst_lvl[] = {'7', '4', '9', '3', '6', '8', '1', '5', '7'};

    std::cout << std::endl << "same tree order: " 
              << same_tree_order(pst, pre, mid, 6, compare) 
              << std::endl << std::endl;

    std::cout << "SRC-PREORDER ";
    p_order(pre, 6);
    std::cout << std::endl;

    std::cout << "MID-PREORDER ";
    p_order(mid, 6);
    std::cout << std::endl;
    
    std::cout << "PST-PREORDER ";
    p_order(pst, 6);
    std::cout << std::endl;
    
    std::cout << "LVL-PREORDER ";
    p_order(lvl, 6);
    std::cout << std::endl;
    
    std::cout << "BST-LVLORDER ";
    p_order(bst_lvl, 9);
    std::cout << std::endl;

    BinaryTree<char> binaryTree(pre, mid, BuildTreeByMidAndPreOrder, 6, print, compare);
    BinaryTree<char> binaryTreeTwo(pst, mid, BuildTreeByMidAndPstOrder, 6, print, compare);
    BinaryTree<char> binaryTreeThree(lvl, mid, BuildTreeByMidAndLvlOrder, 6, print, compare);
    BinaryTree<char> binaryTreeFour(bst_lvl, nullptr, BuildTreeByBSTLvlOrder, 9, print, compare);
    BinaryTree<char> binaryTreeFive(heap, nullptr, BuildTreeByHeapSortOrder, 7, print, compare);

    std::cout << "Binary Tree size: " << binaryTree.size()      << " vs " 
                                      << binaryTreeTwo.size()   << " vs " 
                                      << binaryTreeThree.size() << " vs " 
                                      << binaryTreeFour.size()  << " vs "
                                      << binaryTreeFive.size()  << std::endl;

    std::cout << "Binary Tree depth: " << binaryTree.depth()      << " vs " 
                                       << binaryTreeTwo.depth()   << " vs " 
                                       << binaryTreeThree.depth() << " vs " 
                                       << binaryTreeFour.depth()  << " vs "
                                       << binaryTreeFive.depth()  << std::endl;
    std::cout << std::endl;

    std::cout << "h(k) nodes: ";
    binaryTreeFive.hknodes(2);
    std::cout << std::endl << std::endl;

    std::cout << "DST-PREORDER-1 ";
    binaryTree.pre_traverse();
    std::cout << std::endl;
    
    std::cout << "DST-PREORDER-2 ";
    binaryTreeTwo.pre_traverse();
    std::cout << std::endl;

    std::cout << "DST-PREORDER-3 ";
    binaryTreeThree.pre_traverse();
    std::cout << std::endl;
    
    std::cout << "DST-PREORDER-4 ";
    binaryTreeFour.pre_traverse();
    std::cout << std::endl;
    
    std::cout << "DST-PREORDER-5 ";
    binaryTreeFive.pre_traverse();
    std::cout << std::endl << std::endl;
    
    std::cout << "MID-PREORDER-1 ";
    binaryTree.mid_traverse();
    std::cout << std::endl;
    
    std::cout << "MID-PREORDER-2 ";
    binaryTreeTwo.mid_traverse();
    std::cout << std::endl;
    
    std::cout << "MID-PREORDER-3 ";
    binaryTreeThree.mid_traverse();
    std::cout << std::endl;
    
    std::cout << "MID-PREORDER-4 ";
    binaryTreeFour.mid_traverse();
    std::cout << std::endl;
    
    std::cout << "MID-PREORDER-5 ";
    binaryTreeFive.mid_traverse();
    std::cout << std::endl << std::endl;

    std::cout << "PST-PREORDER-1 ";
    binaryTree.post_traverse();
    std::cout << std::endl;
    
    std::cout << "PST-PREORDER-2 ";
    binaryTreeTwo.post_traverse();
    std::cout << std::endl;
    
    std::cout << "PST-PREORDER-3 ";
    binaryTreeThree.post_traverse();
    std::cout << std::endl;
    
    std::cout << "PST-PREORDER-4 ";
    binaryTreeFour.post_traverse();
    std::cout << std::endl;
    
    std::cout << "PST-PREORDER-5 ";
    binaryTreeFive.post_traverse();
    std::cout << std::endl << std::endl;

    std::cout << "LVL-PREORDER-1 ";
    binaryTree.breadth_traverse();
    std::cout << std::endl;
    
    std::cout << "LVL-PREORDER-2 ";
    binaryTreeTwo.breadth_traverse();
    std::cout << std::endl;
    
    std::cout << "LVL-PREORDER-3 ";
    binaryTreeThree.breadth_traverse();
    std::cout << std::endl;
    
    std::cout << "LVL-PREORDER-4 ";
    binaryTreeFour.breadth_traverse();
    std::cout << std::endl;
    
    std::cout << "LVL-PREORDER-5 ";
    binaryTreeFive.breadth_traverse();
    std::cout << std::endl << std::endl;

    return 0;
}
