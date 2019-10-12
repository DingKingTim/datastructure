#include "queue.h"
#include <iostream>


int main(int argc, char **argv) {
    Queue<int, 5> queue;

    queue.put(1);
    std::cout << "queu size: " << queue.size() << std::endl;
    queue.put(2);
    std::cout << "queu size: " << queue.size() << std::endl;
    queue.put(3);
    std::cout << "queu size: " << queue.size() << std::endl;
    queue.put(4);
    std::cout << "queu size: " << queue.size() << std::endl;
    queue.put(5);
    std::cout << "queu size: " << queue.size() << std::endl;

    while(!queue.empty()) {
        std::cout << queue.get() << " ";
    }
    std::cout << std::endl;
    return 0;
}
