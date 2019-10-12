#ifndef _COMMON_H_
#define _COMMON_H_

typedef bool (*compare_t)(void*, size_t i, size_t j);
typedef bool (*compare_data_t)(void*, void*);
typedef int (*compare_equal_t)(void*, void*);
typedef void (*swap_t)(void*, size_t i, size_t j);

#endif
