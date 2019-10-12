#ifndef _CIRCULAR_LIST_H_
#define _CIRCULAR_LIST_H_
#include <exception>
#include <iostream>

class MemoryException : public std::exception {
    public:
        const char* what() {
            return "no space to save node";
        }
};

class IndexOutException : public std::exception {
    public:
        const char* what() {
            return "index out edage";
        }
};

template <class T>
class Node {
    public:
        T data;
        Node* next;
};

template <class T>
class CircularList {
    private:
        size_t size_;
        Node<T>* tail_;

    public:
        CircularList();
        void append(T data);
        void del(T data);
        void print() const;
        size_t size() const;
        Node<T> operator[](size_t idx) const;

};

template <class T>
CircularList<T>::CircularList() : tail_(nullptr), size_(0) {
}

template <class T>
void CircularList<T>::append(T data) {
    Node<T>* node = new Node<T>;
    node->data = data;
    node->next = nullptr;

    this->size_ ++;
  
    if (this->tail_ == nullptr) {
        this->tail_ = node;
        this->tail_->next = this->tail_;
        return;
    }

    Node<T>* head = this->tail_->next;
    this->tail_->next = node;
    node->next = head;
    this->tail_ = node;
}

template <class T>
void CircularList<T>::del(T data) {

    if (nullptr == this->tail_) {
        return;
    }

    Node<T>* pre = nullptr;
    Node<T>* tmp = this->tail_->next;

    while (tmp != this->tail_) {
        if (tmp->data == data) {
            if (nullptr == pre) {
                this->tail_->next = this->tail_;
                delete tmp;
                tmp = nullptr;
                this->size_--;
                return;
            } else {
                pre->next = tmp->next;
                delete tmp;
                tmp = nullptr;
                this->size_--;
                return;
            }
        }
       
        pre = tmp;
        tmp = tmp->next;
    }

    if (this->tail_->data == data) {
        if (nullptr != pre) {
            pre->next = this->tail_->next;
        }
        delete this->tail_;
        this->tail_ = pre;
        this->size_--;
    } 
}




template <class T>
void CircularList<T>::print() const {
    if (nullptr == this->tail_) {
        return;
    }

    Node<T>* tmp = this->tail_->next;
    while (tmp != this->tail_) {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    std::cout << tmp->data << " " << std::endl;
}

template <class T>
Node<T> CircularList<T>::operator[](size_t idx) const {
    if (nullptr == this->tail_) {
        throw IndexOutException();
    }

    size_t i = 0;
    Node<T>* tmp = this->tail_->next;
    while (tmp != this->tail_) {
        if (i == idx) {
            return *tmp;
        }
        i++;
        tmp = tmp->next;
    }

    if (i == idx) {
        return *tmp;
    }

    throw IndexOutException();
}

template <class T>
size_t CircularList<T>::size() const {
    return this->size_;
}

#endif
