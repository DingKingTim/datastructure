#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <exception>

class FullException : std::exception {
    public:
        const char* what() {
            return "Queue is full";
        }
};

class EmptyException : std::exception {
    public:
        const char* what() {
            return "Queue is empty";
        }
};

template<class T, size_t cap>
class Queue {
    private:
        size_t len_;
        size_t front_;
        size_t rear_;
        T queue_[cap];

    public:
        Queue();
        ~Queue();
        T get();
        void put(T data);
        size_t capacity() const;
        bool empty() const;
        bool full() const;
        size_t size() const;
};

template<class T, size_t cap>
Queue<T, cap>::Queue() : len_(0), front_(0), rear_(cap-1) {
}

template<class T, size_t cap>
Queue<T, cap>::~Queue() {
}

template<class T, size_t cap>
void Queue<T, cap>::put(T data) {
    if (this->full()) {
        throw FullException();
    }

    this->rear_ = (this->rear_ + 1) % cap;
    this->queue_[this->rear_] = data;
    this->len_++;
}

template<class T, size_t cap>
T Queue<T, cap>::get() {
    if (this->empty()) {
        throw EmptyException();
    }

    T item = this->queue_[this->front_];
    this->front_ = (this->front_ + 1) % cap;
    this->len_--;
    return item;
}

template<class T, size_t cap>
size_t Queue<T, cap>::size() const {
    return this->len_;
}

template<class T, size_t cap>
size_t Queue<T, cap>::capacity() const {
    return cap;
}

template<class T, size_t cap>
bool Queue<T, cap>::empty() const {
    return this->len_ == 0;
}

template<class T, size_t cap>
bool Queue<T, cap>::full() const {
    return this->len_ == cap;
}
#endif
