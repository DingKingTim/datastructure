> [1、基本的一个二叉树](#1)
>
> [2、二叉树的基本性质](#2)



<h4 id='1'> 1、基本的一个二叉树 </h4>

![binary tree](https://github.com/DingKingTim/datastructure/blob/master/tree/media/base_binarytree.jpeg)



<h4 id='2'> 2、二叉树的基本性质 </h4>

- 第l层上的最大节点数：**`2^(l-1)`**

   ```c
   #define MAX_NODE_OF_LEVEL(l) pow(2, (l)-1)
   ```

- 高度h的树拥有的最大节点数：**`(2^h) - 1`**

  ```c
  #define MAX_NODE_OF_HIGH(h) (pow(2, h) - 1)
  ```
