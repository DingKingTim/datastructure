#include "bsttree.h"
#include <iostream>

int compare(void* d1, void* d2) {
    int c1 = *((int*)d1);
    int c2 = *((int*)d2);

    if (c1 == c2) {
        return 0;
    } else if (c1 > c2) {
        return 1;
    } else {
        return -1;
    }
}

void print(void* data) {
    int c = *((int*)data);
    std::cout << c << " ";
}

int main(void) {
        
    BstTree<int> bsttree(print, compare);

    bsttree.insert(5);
    bsttree.insert(2);
    bsttree.insert(9);
    bsttree.insert(1);
    bsttree.insert(4);
    bsttree.insert(7);
    bsttree.insert(6);
    bsttree.insert(16);
    bsttree.insert(15);

    std::cout << "insert over and porder: ";
    bsttree.preorder();
    std::cout << std::endl << std::endl;

    bsttree.del(9);
    std::cout << "delete 9 over and porder: ";
    bsttree.preorder();
    std::cout << std::endl << std::endl;

    bsttree.del(7);
    std::cout << "delete 7 over and porder: ";
    bsttree.preorder();
    std::cout << std::endl << std::endl;

    return 0;
}
