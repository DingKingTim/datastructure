#ifndef _COMMON_H_
#define _COMMON_H_
#include <cmath>

// 1) The maximum number of nodes at level 'l' of a binary tree is 2^(l-1).
#define MAX_NODE_OF_LEVEL(l) pow(2, (l)-1)

// 2) Maximum number of nodes in a binary tree of height 'h' is 2^h - 1.
#define MAX_NODE_OF_HIGH(h) (pow(2, h) - 1)

/*
 *  0 => d1 == d2
 *  1 => d1 >  d2
 * -1 => d1 <  d2
 */
typedef int (*compare_t)(void *d1, void *d2);
typedef void (*print_t)(void *d1);

#endif
