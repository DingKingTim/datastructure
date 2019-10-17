二叉搜索树

> [1、平衡二叉搜索树特点](#1)
>
> [2、操作情景](#2)
>>
>> [2.1、右旋转](#2.1)
>


由于二叉搜索树在极度恶劣情况下导致左右极度不平衡，其搜索时间和线性搜索无区别，因此引入了平衡，使左右高度近乎一样，或者完全平衡。


<h4 id='1'> 1、平衡二叉搜索树特点 </h4>

- 每一个节点左右高度 **`| l_height - r_height | <= 1`**
- 由于插入时可能频繁旋转树，因此插入效率不高
- 搜索效率比较高，**`log(n)`**

<h4 id='2'> 2、操作情景 </h4>

为了操作方便，给每个节点增加高度属性，所以节点定义如下

```
template <class T>
class Node {
    public:
        T data;
        
        // 记录节点的高度
        int height;
        Node* l_child;
        Node* r_child;
};
```

<h5 id='2.1'> 2.1、右旋转 </h5>

树本来平衡，由于左边插入了一个元素，导致坐高，有底，此时右旋转，图示如下

![](https://github.com/DingKingTim/datastructure/blob/master/tree/media/left-rotate.png)
		

```c
// 1. 暂存不平衡节点的左子树
Node<T>* nl = node->l_child;

// 2. 暂存不平衡节点的左子树根节点的右子树
Node<T>* nlr = nl->r_child;

// 3. 旋转第一步
nl->r_child = node;

// 4. 旋转第二步
node->l_child = nlr;

// 5. 旋转后不平衡节点的高度发生了变化，重新计算
node->height = this->_max(this->_height(node->l_child), 
		      this->_height(node->r_child)) + 1;

// 6. 右子树的高度发生变化，新根节点的高度调节
nl->height = this->_max(this->_height(nl->l_child),
		    this->_height(nl->r_child)) + 1;

return nl;
```
