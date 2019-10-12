#ifndef _SORT_H_
#define _SORT_H_
#include <iostream>
#include "common.h"


#define PARENT(i) ((i) >> 1)
#define LEFT(i) ((i) << 1)
#define RIGHT(i) (LEFT(i) + 1)
#define LAST_PARENT(n) ((n) >> 1)


template<class T, int size>
class Sort {
    public:
        Sort(compare_t m, swap_t s);
        Sort(compare_data_t m, swap_t s);

        void select_sort(T* data);
        void insert_sort(T* data);
        void merge_sort(T* data);
        void heap_sort(T *data);
        void bubble_sort(T *data);
        void quick_sort(T *data);

    private:
        void _merge_sort(T* data, int l, int r);
        void _heapify(T* a, int len, int i);
        void _build_heap(T* a);
        int _partition(T *data, int low, int high);
        void _quick_sort(T *data, int low, int high);
        void _merge(T* data, int l, int r, int m);

    private:
        compare_t compare_;
        compare_data_t compare_data_;
        swap_t swap_;
};

template<class T, int size>
Sort<T, size>::Sort(compare_t m, swap_t s) : compare_(m), swap_(s) {
    this->compare_data_ = NULL;
}

template<class T, int size>
Sort<T, size>::Sort(compare_data_t m, swap_t s) : compare_data_(m), swap_(s) {
}

template<class T, int size>
void Sort<T, size>::select_sort(T* data) {
    for (size_t i=0; i<(size-1); i++) {
        size_t m = i;
        for (size_t j=i+1; j<size; j++) {
            if (this->compare_(data, m, j)) {
                m = j;
            }
        }
        if (m != i) {
            this->swap_(data, m, i);
        }
    }
}

template<class T, int size>
void Sort<T, size>::insert_sort(T* data) {
    int i, j, k;

    for (i=1; i<size; i++) {
        T key = data[i];
        for (j=i-1; j>=0; j--) {
            if (this->compare_data_(&data[j], &key)) {
                data[j+1] = data[j];
                continue;
            }
            break;
        }
        data[j+1] = key;
    }
}

template<class T, int size>
void Sort<T, size>::_merge(T* data, int l, int r, int m) {
    int l_size = m - l + 1;
    int r_size = r - m;

    // l 到r这段空间需要重现放数据
    // 因此开辟空间临时保存数据
    T *la = new T[l_size];
    std::memset(la, 0, l_size);
    
    T *ra = new T[r_size];
    std::memset(ra, 0, r_size);

    for (int i=0; i<l_size; i++) {
        la[i] = data[l + i];
    }

    for (int j=0; j<r_size; j++) {
        ra[j] = data[m + j + 1];
    }

    int i=0;
    int j=0;
    int k=l;

    while (i<l_size && j<r_size) {
        if (this->compare_data_(&la[i], &ra[i])) {
            data[k] = la[i];
            i++;
        } else {
            data[k] = ra[j];
            j++;
        }
        k++;
    }

    while (i<l_size) {
        data[k] = la[i];
        i++;
        k++;
    }

    while (j<r_size) {
        data[k] = ra[j];
        j++;
        k++;
    }

    delete [] la;
    delete [] ra;
}

template<class T, int size>
void Sort<T, size>::_merge_sort(T* data, int l, int r) {
    if (l < r) {
        int mid = l + ((r - l) >> 1);
        
        this->_merge_sort(data, l, mid);
        this->_merge_sort(data, mid+1, r);
        this->_merge(data, l, r, mid);
    }
}

template<class T, int size>
void Sort<T, size>::merge_sort(T* data) {
    this->_merge_sort(data, 0, size-1);
}

template <class T, int size>
void Sort<T, size>::_heapify(T* a, int len, int i) {
    
    int left = LEFT(i);
    int right = RIGHT(i);
    int large = i;

    if (left <= len && this->compare_(a, left-1, i-1)) {

        if (right <= len) {
            large = this->compare_(a, left-1, right-1) ? left : right;
        } else {
            large = left;
        }

    } else if (right <= len && this->compare_(a, right-1, i-1)) {

        large = this->compare_(a, left-1, right-1) ? left : right;
    }

    if (large != i) {
        this->swap_(a, i-1, large-1);
        this->_heapify(a, len, large);	
    }
}

template <class T, int size>
void Sort<T, size>::_build_heap(T* a) {

    int i = LAST_PARENT(size);
    for (; i>0; --i) {
        this->_heapify(a, size, i);
    }
}

template <class T, int size>
void Sort<T, size>::heap_sort(T *a) {

    this->_build_heap(a);

    int i=0;
    int range_idx = size;
    while (range_idx > 1) {
        this->swap_(a, 0, range_idx-1);
        range_idx -= 1;
        this->_heapify(a, range_idx, 1);
        i++;
    }
}

template <class T, int size>
void Sort<T, size>::bubble_sort(T *data) {
    for (int i=size-1; i>0; i--) {
        for (int j=0; j<i; j++) {
            if (this->compare_(data, j, j+1)) {
                this->swap_(data, j, j+1);
            }
        }
    }
}

template <class T, int size>
int Sort<T, size>::_partition(T *data, int low, int high) {
    int pivot_idx = high;
   
    int i = low;
    int j = high;

    while (i != j) {
        while (this->compare_(data, j, pivot_idx)) {
            j--;
        }

        while (i!=j && !this->compare_(data, i, pivot_idx)) {
            i++;
        }
        this->swap_(data, i, j);
    }

    return i;
}

template <class T, int size>
void Sort<T, size>::_quick_sort(T *data, int low, int high) {
    if (low < high) {
        int mid = this->_partition(data, low, high);
        this->_quick_sort(data, low, mid-1);
        this->_quick_sort(data, mid+1, high);
    }
}

template <class T, int size>
void Sort<T, size>::quick_sort(T *data) {
    this->_quick_sort(data, 0, size-1);
}

#endif
