#include "double_list.h"


int main(void) {
    std::cout << "Append: " << std::endl;
    DoubleList<int> doubleList;
    doubleList.append(1);
    doubleList.append(2);
    doubleList.append(3);
    doubleList.print();

    try {
        Node<int>* node = doubleList[1];
        std::cout << "node-1: " << node->data << std::endl;
        node = doubleList[-2];
        std::cout << "node[-2]: " << node->data << std::endl;
        node = doubleList[6];
        std::cout << "node[6]: " << node->data << std::endl;
    } catch (std::exception &ex) {
        std::cout << "exception: " << ex.what() << std::endl;
    }

    doubleList[0]->data = 5;
    doubleList.print();
    return 0;
}
