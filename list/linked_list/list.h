#ifndef _LIST_H_
#define _LIST_H_
#include <cstdio>
#include <iostream>
#include <exception>

class NullNodeError : public std::exception {
    public:
        const char* what() {
            return "null node error";
        }
};


class MemoryNodeError : public std::exception {
    public:
        const char* what() {
            return "memory of node not enough";
        }
};

class IndexOutError : public std::exception {
    public:
        const char* what() {
            return "index out error";
        }
};

template <class T>
class Node {
    public:
        T data;
        Node* next;
};

template <class T>
class List {
    public:
        Node<T>* head_;

    public:
        List();
        void print() const;
        void push(T data);
        void append(T data);
        void insert_after(Node<T> *node, T data);
        void del(T data);
        size_t size();
        void del_pos(int pos);
        void reverse();
        void select_sort();
        List<T> operator+(const List<T>& t) const;
        Node<T>* operator[](size_t idx);
        void operator+=(const List<T>& t);
};

template <class T>
List<T>::List() {
    this->head_ = nullptr;
}

template <class T>
void List<T>::print() const {
    int i = 0;
    Node<T>* tmp = this->head_;

    while (tmp != nullptr) {
        // std::cout << i << ": " << tmp->data << std::endl;
        std::cout << tmp->data << " ";
        tmp = tmp->next;
        i++;
    }
    std::cout << std::endl;
}

template <class T>
void List<T>::push(T data) {
    Node<T> *node = new Node<T>;
    node->data = data;
    node->next = this->head_;
    this->head_ = node;
}

template <class T>
void List<T>::insert_after(Node<T> *pre, T data) {
    if (nullptr == pre || NULL == pre) {
        throw NullNodeError();
    }

    Node<T> *node = new Node<T>;
    node->data = data;
    node->next = pre->next;
    pre->next = node;
}


template <class T>
void List<T>::append(T data) {
    Node<T> *node = new Node<T>;
    node->data = data;
    node->next = nullptr;

    if (this->head_ == nullptr) {
        this->head_ = node;
        return;
    }

    Node<T> *pre = this->head_;
    while(pre != nullptr) {
        if (pre->next == nullptr) {
            pre->next = node;
            break;
        } else {
            pre = pre->next;
        }
    }
}

template <class T>
void List<T>::del(T data) {
    Node<T>* pre = nullptr;
    Node<T>* cur = this->head_;

    while (nullptr != cur) {
        if (cur->data == data) {
            if (nullptr == pre) {
                this->head_ = this->head_->next;
                delete cur;
                return;

            } else {
                pre->next = cur->next;
                delete cur;
            }
        }

        pre = cur;
        cur = cur->next;
    }
}

template <class T>
void List<T>::del_pos(int pos) {
    int i = 0;
    Node<T>* pre = nullptr;
    Node<T>* cur = this->head_;

    while (nullptr != cur) {
        if (i == pos) {
            if (nullptr == pre) {
                this->head_ = this->head_->next;
                delete cur;
                return;

            } else {
                pre->next = cur->next;
                delete cur;
            }
        }

        i++;
        pre = cur;
        cur = cur->next;
    }

    if (pos >= i) {
        throw IndexOutError();
    }
}

template <class T>
size_t List<T>::size() {
    size_t i = 0;
    Node<T>* node = this->head_;
    while (nullptr != node) {
        i++;
        node = node->next;
    }

    return i;
}

template <class T>
void List<T>::reverse() {
    Node<T>* pre {nullptr};
    Node<T>* next {nullptr};
    Node<T>* cur = this->head_;

    while (cur != nullptr) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    this->head_ = pre;
}

template <class T>
List<T> List<T>::operator+(const List<T>& t) const {
    List<T> sum;
    Node<T>* me = this->head_;
    Node<T>* th = t.head_;

    this->print();
    t.print();

    while (me != nullptr && th != nullptr) {
        if (me->data < th->data) {
            sum.append(me->data);
            me = me->next;
        } else {
            sum.append(th->data);
            th = th->next;
        }
    }

    while (me != nullptr) {
        sum.append(me->data);
        me = me->next;
    }

    while (th != nullptr) {
        sum.append(th->data);
        th = th->next;
    }

    return sum;
}

template <class T>
Node<T>* List<T>::operator[](size_t idx) {
    size_t i = 0;
    Node<T>* node = this->head_;
    while (nullptr != node) {
        if (i == idx) {
            return node;
        }
        node = node->next;
        i++;
    }

    throw IndexOutError();
}

template <class T>
void List<T>::operator+=(const List<T>& t) {
    Node<T>* node = t.head_;
    while (nullptr != node) {
        this->append(node->data);
        node = node->next;
    }
}

template <class T>
void List<T>::select_sort() {

}

#endif
