> [1、基本的一个二叉树](#1)
>
> [2、二叉树的基本性质](#2)
>
> [3、遍历方式](#3)



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

<h4 id='3'> 3、遍历方式 </h4>

- 深度优先遍历

   - 前序遍历: 根 --> 左 --> 右
   
   ```c
   A  B  D  E  C  F
   ```
   
   - 中序遍历: 左 --> 根 --> 右
   
   ```c
   D  B  E  A  F  C
   ```
   
   - 后序遍历: 左 --> 右 --> 根
   
   ```c
   D  E  B  F  C  A
   ```
   
- 宽度优先遍历: 

    - 左 --> 右 --下一层--> 左 --> 右
    
    ```C
    A  B  C  D  E  F
    ```
    
<h4 id='4'> 4、给定序列创建树 </h4>

单个的序列无论是前序，中序，后序，还是顺序都无法唯一确定一棵树

- 唯一确定一棵树的三种方式

   - 中序和前序组合
   
   - 中序和后序组合
   
   - 中序和顺序组合
   
 - 中序和前序组合算法：
 
   前序节点在中序中的位置idx，在前序中idx的左边节点为该节点的左节点，idx右边的节点为右节点

 
   - **`[start, end]`** 序列中顺序取出一个元素，创建节点 **`node`**
   - 查找新创建节点 **`node`** 在中序中的位置 **`idx`**
   - 以 **`idx`** 为中心，将前序分成两部分，**`idx_left`** 和 **`idx_right`**
   - **`idx_left`** 左边的元素指向新创建节点 node的左子树，其范围为 **`[start, idx-1]`**, 在此区间上重复上面步骤
   - **`idx_right`** 右边的元素指向新创建节点 node 的右子树，其范围为 **`[idx+1, end]`**，在此区间上重复上面步骤
   
   ```
    static int index = 0;

    if (start > end) {
        return nullptr;
    }
    
    // 顺序取节点，并创建
    Node<T>* node = new Node<T>(pre[index++]);
    
    // 只有一个节点返回
    if (start == end) {
        this->size_ += 1;
        return node;
    }
    
    // 查找新创建节点在中序中的位置
    int midIndex = this->_search(mid, node->data, start, end);
    
    // 前序中 [start, mindIndex-1] 左边为该节点的左节点
    node->l_child = this->_buildTreeWithPreMidOrder(pre, mid, start, midIndex-1);
    
    // 前序中 [mindIndex-1,end] 右边为该节点的右节点
    node->r_child = this->_buildTreeWithPreMidOrder(pre, mid, midIndex+1, end);

    this->size_ += 1;

    // 返回根节点
    return node;
   ```
- 中序和后序组合

后序和前序所不同之处在于根节点在后序中处于序列的最后，因此只要倒着取，逐个创建节点即可

   ```
    // 索引开始指向序列的末尾
    static int index = end;

    if (end < start) {
        return nullptr;
    }

    // 1> 创建节点，序列忘前移动
    Node<T>* node = new Node<T>(pst[index--]);

    if (end == start) {
        this->size_++;
        return node;
    }

    // 2> 中序中搜索新创建节点的位置
    int midIndex = this->_search(mid, node->data, start, end);

    // 3> 后序中该位置右边的节点为新创建节点的右节点
    node->r_child = this->_buildTreeWithPostMidOrder(pst, mid, midIndex+1, end);

    // 4> 后续中该位置左边的节点为新创建节点的左节点
    node->l_child = this->_buildTreeWithPostMidOrder(pst, mid, start, midIndex-1);

    this->size_++;
    return node;
   ```
   
- 前序和顺序组合

   - 创建子序列的第一个节点 **`node`**
   - 查找该节点 **`node`** 在中序中的位置 **`idx`**
   - 中序中，以 **`idx`** 为轴，左边为 **`idx`** 节点对应的左子树的节点集合 **`l_set`** ，右边为该节点对应的右子树的集合 **`r_set`**
   - 在顺序中找出中序序列 **`l_set`** 的所有位置，并对 **`l_set`** 按照顺序中的位置重新排列，组成新的顺序序列，记为 **`l_lvl`**
   - 在顺序中找出中序序列 **`r_set`** 的所有位置，并对 **`r_set`** 按照顺序中的位置重新排列，组成新的顺序序列，记为 **`r_lvl`**
   - **`node`** 的左节点指向 **`l_lvl`** 创建的根节点，递归 **`l_lvl`**
   - **`node`** 的右节点指向 **`r_lvl`** 创建的根节点，递归 **`r_lvl`**
   
   ```
   // 1> 创建根节点，顺序节点的第一个元素为根节点
    Node<T> *node = new Node<T>(lvl[0]);
    if (start == end) {
        this->size_++;
        return node;
    }
    
    // 找出中序中的位置
    int rootIdxInMid = this->_search(mid, node->data, start, end);

    int l_lvl_size = rootIdxInMid - start;
    int r_lvl_size = end - rootIdxInMid;

    // 利用中序左边和右边的元素构建新的序列
    T* l_lvl = this->_searchMidInLvl(mid, start, rootIdxInMid-1, lvl, len);
    T* r_lvl = this->_searchMidInLvl(mid, rootIdxInMid + 1, end, lvl, len);
    
    // 根节点指向
    node->l_child = this->_buildTreeWithLvlMidOrder(l_lvl, mid, start, rootIdxInMid-1, l_lvl_size);
    node->r_child = this->_buildTreeWithLvlMidOrder(r_lvl, mid, rootIdxInMid+1, end, r_lvl_size);
     
    return node;
   ```




