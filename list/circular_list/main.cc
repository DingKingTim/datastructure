#include "circular_list.h"


int main(int argc, char **argv) {
    CircularList<int> circularList;

    std::cout << "CircularList append: " << std::endl;
    circularList.append(1);
    circularList.append(2);
    circularList.append(3);
    circularList.print();
    std::cout << std::endl << "CircularList operator []: " << std::endl;
    Node<int> node = circularList[2];
    std::cout << "node-2: " << node.data << std::endl;
    
    std::cout << std::endl << "CircularList size(): " << std::endl;
    std::cout << "size: " << circularList.size() << std::endl;
    
    std::cout << std::endl << "CircularList del(): " << std::endl;
    circularList.del(2);
    circularList.print();
    
    circularList.del(1);
    circularList.print();
   
    circularList.del(4);
    circularList.print();
   
    circularList.del(3);
    circularList.print();
    return 0;
}
