#ifndef _DOUBLE_LIST_H_
#define _DOUBLE_LIST_H_
#include <iostream>
#include <exception>

class BlankListError : public std::exception {
    public:
        const char* what() {
            return "list is blank";
        }
};

class NodeNotFoundError : public std::exception {
    public:
        const char* what() {
            return "node not found";
        }
};

class OutBoundaryError : public std::exception {
    public:
        const char* what() {
            return "index out boundary";
        }
};

template <class T>
class Node {
    public:
        Node(T data) : data(data), pre(nullptr), next(nullptr) {}
        T data;
        struct Node* pre; 
        struct Node* next; 
};


template <class T>
class DoubleList {
    private:
        size_t size_;
        Node<T>* head_;
        Node<T>* tail_;

    public:
        DoubleList();
        void print() const;
        void reverse();
        void append(T data);
        Node<T>* operator[](int idx);
        void insert(Node<T>* node, T data);

};

template <class T>
DoubleList<T>::DoubleList() : head_(nullptr), tail_(nullptr) {
}

template <class T>
void DoubleList<T>::append(T data) {
    Node<T>* node = new Node<T>(data);

    if (nullptr == this->head_) {
        this->head_ = node;
        this->tail_ = this->head_;
        return;
    }

    node->pre = this->tail_;
    this->tail_->next = node;
    this->tail_ = node;
    this->size_++;
}

template <class T>
void DoubleList<T>::insert(Node<T>* pre, T data) {
    if (this->tail_ == nullptr) {
        throw BlankListError();
    }

    Node<T>* node = new Node<T>(data);
    Node<T>* tmp = this->head_;
    while (tmp != nullptr) {
        if (tmp == pre) {
            pre->pre = tmp;
            pre->next = tmp->next;
            tmp->next = pre;
            this->size_++;
            return;
        }
    }

    throw NodeNotFoundError();
}


template <class T>
void DoubleList<T>::print() const {
    Node<T>* node = this->head_;
    while(node != nullptr) {
        std::cout << node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

/*
template <class T>
Node<T> DoubleList<T>::operator[](int idx) const {
    size_t index = idx;
    if (idx < 0) {
        index = this->size_ + idx;
    }

    if (index > this->size_ || index < 0) {
        throw OutBoundaryError();
    }

    size_t i = 0;
    Node<T>* node = this->head_;
    while (node != nullptr) {
        if (i == index) {
            return *node;
        }
        node = node->next;
        i++;
    }
    throw OutBoundaryError();
}
*/

template <class T>
Node<T>* DoubleList<T>::operator[](int idx) {
    size_t index = idx;
    if (idx < 0) {
        index = this->size_ + idx;
    }

    if (index > this->size_ || index < 0) {
        throw OutBoundaryError();
    }

    size_t i = 0;
    Node<T>* node = this->head_;
    while (node != nullptr) {
        if (i == index) {
            return node;
        }
        node = node->next;
        i++;
    }
    throw OutBoundaryError();
}

#endif
