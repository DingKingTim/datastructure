#include "avltree.h"
#include <iostream>

void print(void* data) {
    int d = *((int*)data);
    std::cout << d << " ";
}

int compare(void* data1, void* data2) {
    int d1 = *((int*)data1);
    int d2 = *((int*)data2);

    if (d1 > d2) return 1;
    else if(d1 < d2) return -1;
    else return 0;
}

void rotate_right() {
    AvlTree<int> avltree(compare, print);
    avltree.insert(13);
    avltree.insert(10);
    avltree.insert(15);
    avltree.insert(16);
    avltree.insert(5);
    avltree.insert(11);
    avltree.insert(4);
    avltree.insert(8);
    avltree.insert(3);
    avltree.preorder();
    std::cout << " | ";
    avltree.midorder();
    std::cout << std::endl << std::endl;
}

void rotate_left() {
    AvlTree<int> avltree(compare, print);
    avltree.insert(30);
    avltree.insert(5);
    avltree.insert(35);
    avltree.insert(32);
    avltree.insert(40);
    avltree.insert(45);
    avltree.preorder();
    std::cout << " | ";
    avltree.midorder();
    std::cout << std::endl << std::endl;
}

void rotate_left_right() {
    AvlTree<int> avltree(compare, print);
    avltree.insert(13);
    avltree.insert(10);
    avltree.insert(15);
    avltree.insert(16);
    avltree.insert(5);
    avltree.insert(11);
    avltree.insert(4);
    avltree.insert(6);
    avltree.insert(7);
    avltree.preorder();
    std::cout << " | ";
    avltree.midorder();
    std::cout << std::endl << std::endl;
}

void rotate_right_left() {
    AvlTree<int> avltree(compare, print);
    avltree.insert(5);
    avltree.insert(2);
    avltree.insert(7);
    avltree.insert(1);
    avltree.insert(4);
    avltree.insert(6);
    avltree.insert(9);
    avltree.insert(3);
    avltree.insert(16);
    avltree.insert(15);
    avltree.preorder();
    std::cout << " | ";
    avltree.midorder();
    std::cout << std::endl << std::endl;
}

void node_del() {
    AvlTree<int> avltree(compare, print);
    avltree.insert(5);
    avltree.insert(2);
    avltree.insert(7);
    avltree.insert(1);
    avltree.insert(4);
    avltree.insert(6);
    avltree.insert(9);
    avltree.insert(3);
    avltree.insert(16);
    avltree.insert(15);

    avltree.del(15);
    avltree.preorder();
    std::cout << " | ";
    avltree.midorder();
    std::cout << std::endl << std::endl;

    avltree.del(9);
    avltree.preorder();
    std::cout << " | ";
    avltree.midorder();
    std::cout << std::endl << std::endl;
}

int main(void) {
    std::cout << "1. right rotate: ";
    rotate_right();
    
    std::cout << "2. left rotate: ";
    rotate_left();
    
    std::cout << "3. left right rotate: ";
    rotate_left_right();
    
    std::cout << "3. right left rotate: ";
    rotate_right_left();
  
    std::cout << "4. del node: ";
    node_del();

    return 0;
}
