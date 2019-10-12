#include "list.h"


int main(int argc, char **argv) {

    List<int> *list = new List<int>;

    std::cout << "push. " << std::endl;
    list->push(1);
    list->push(2);
    list->push(3);
    list->print();
    
    std::cout << std::endl << "append. " << std::endl;
    list->append(4);
    list->append(5);
    list->append(6);
    list->print();

    std::cout << std::endl << "del. " << std::endl;
    list->del(4);
    list->del(6);
    list->print();

    std::cout << std::endl << "insert after. " << std::endl;
    list->insert_after(list->head_, 9);
    list->print();

    std::cout << std::endl << "del pos. 2" << std::endl;
    list->del_pos(2);
    list->print();

    try {
        list->del_pos(133);
    } catch (std::exception &ex) {
        std::cout << std::endl << "exception found: " << ex.what() << std::endl;
    }
    
    size_t size = list->size();
    std::cout << std::endl << "size" << size << std::endl;
    printf("size: %ld\n", size);

    std::cout << std::endl << "reverse. " << std::endl;
    list->reverse();
    list->print();

    std::cout << std::endl << "merge sort list. " << std::endl;
    List<int> list1;
    list1.append(5);
    list1.append(10);
    list1.append(15);
    list1.print();
    
    List<int> list2;
    list2.append(2);
    list2.append(3);
    list2.append(4);
    list2.append(20);
    list2.print();

    std::cout << std::endl << "list operator + " << std::endl;
    List<int> sum = list1 + list2;
    sum.print();

    std::cout << std::endl << "list operator +=. " << std::endl;
    list1 += list2;
    list1.print();

    std::cout << std::endl << list1[4].data << std::endl;
    return 0;
}

