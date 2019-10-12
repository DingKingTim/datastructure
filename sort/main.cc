#include <iostream>
#include <ctime>
#include "sort.h"
#include "search.h"

#define SIZE 10

bool compare(void *d, size_t i, size_t j) {
    int *arr = (int*)d;
    return arr[i] < arr[j];
}

bool compare_data(void *d1, void* d2) {
    int a = *((int*)d1);
    int b = *((int*)d2);
    return a < b;
}


int compare_equea(void *d1, void* d2) {
    int a = *((int*)d1);
    int b = *((int*)d2);

    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}

/*
 * 位异或交换时两个数字不能相等
 */
void swap(void *d, size_t i, size_t j) {
    int *arr = (int*)d;
    if (arr[i] == arr[j]) {
        return;
    }

    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[i] ^ arr[j];
    arr[i] = arr[i] ^ arr[j];
}

void print(int *arr, int size) {
    for (size_t i=0; i<size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int* generate_data(int size) {
	int *arr = new int[size];
    std::memset(arr, 0, size);

	for (int i=0; i<size; i++) {
		int x = 1 + std::rand()/((RAND_MAX + 1u)/99);
        arr[i] = x;
	}

	return arr;
}

void search(int *data, int size, int i) {
    Search<int> search(compare_equea);
    std::cout << "Search index: data[" << i << "]: " << data[i] << std::endl;
    std::cout << "1. linear   : " << search.linear_search(data, size, data[i]) << std::endl;
    std::cout << "2. binary   : " << search.binary_search(data, size, data[i]) << std::endl;
}

void select_sort() {
    int *arr = generate_data(SIZE);
    print(arr, SIZE);
    
    Sort<int, SIZE> sort(compare, swap);
    sort.select_sort(arr);
    print(arr, SIZE);
    search(arr, SIZE, 4);
}

void merge_sort() {
    int *arr = generate_data(SIZE);
    print(arr, SIZE);
    
    Sort<int, SIZE> sort(compare_data, swap);
    sort.merge_sort(arr);
    print(arr, SIZE);
    search(arr, SIZE, 4);
}

void insert_sort() {
    int *arr = generate_data(SIZE);
    print(arr, SIZE);

    Sort<int, SIZE> sort(compare_data, swap);
    sort.insert_sort(arr);
    print(arr, SIZE);
    search(arr, SIZE, 4);
}

void heap_sort() {
    int *arr = generate_data(SIZE);
    print(arr, SIZE);

    Sort<int, SIZE> sort(compare, swap);
    sort.heap_sort(arr);
   
    print(arr, SIZE);
    search(arr, SIZE, 4);
}

void bubble_sort() {
    int *arr = generate_data(SIZE);
    print(arr, SIZE);

    Sort<int, SIZE> sort(compare, swap);
    sort.bubble_sort(arr);
   
    print(arr, SIZE);
    search(arr, SIZE, 4);
}

void quick_sort() {
    int *arr = generate_data(SIZE);
    print(arr, SIZE);

    Sort<int, SIZE> sort(compare, swap);
    sort.quick_sort(arr);
   
    print(arr, SIZE);
    search(arr, SIZE, 4);
}



int main() {
    std::srand(std::time(nullptr));

    std::cout << "1. select sort test. " << std::endl;
    select_sort();
    
    std::cout << std::endl << "2. insert sort test. " << std::endl;
    insert_sort();
    
    std::cout << std::endl << "3. merge sort test. " << std::endl;
    merge_sort();

    std::cout << std::endl << "4. heap sort test. " << std::endl;
    heap_sort();

    std::cout << std::endl << "5. bubble sort test. " << std::endl;
    bubble_sort();

    std::cout << std::endl << "6. quick sort test. " << std::endl;
    quick_sort();

    return 0;
}
