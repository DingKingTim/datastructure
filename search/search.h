#ifndef _SEARCH_H_
#define _SEARCH_H_
#include "common.h"

template <class T>
class Search {
    public:
        Search(compare_equal_t e) : compare_equal_(e) {}
        int linear_search(T *data, int size, T d);
        int binary_search(T *data, int size, T d);

    private:
        int _binary_search(T *data, int l, int r, T d);

    private:
        compare_equal_t compare_equal_;
};

template <class T>
int Search<T>::linear_search(T *data, int size, T d) {
    for (int i=0; i<size; i++) {
        if (0 == this->compare_equal_(&(data[i]), &d)) {
            return i;
        }
    }

    return -1;
}

template <class T>
int Search<T>::_binary_search(T *data, int l, int r, T d) {
    int mid = l + ((r-l) >> 1);
    int ret = this->compare_equal_(&(data[mid]), &d);
    if (ret > 0) {
        this->_binary_search(data, mid+1, r, d);
    } else if (ret < 0) {
        this->_binary_search(data, l, mid-1, d);
    } else {
        return mid;
    }

    return -1;
}

template <class T>
int Search<T>::binary_search(T *data, int size, T d) {
    return this->_binary_search(data, 0, size-1, d); 
}

#endif
