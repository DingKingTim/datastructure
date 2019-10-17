二叉搜索树

> [1、基本的一个二叉树](#1)
>
> [2、二叉树的基本性质](#2)
>
> [3、遍历方式](#3)
>
> [4、给定序列创建树](#4)
> 
> > [4.1、中序和前序组合算法](#4.1)
> > 
> > [4.2、中序和后序组合算法](#4.2)
> > 
> > [4.3、中序和顺序组合算法](#4.3)
> > 
> > [4.4、构建堆](#4.4)
> 



<h4 id='1'> 1、二叉搜索树的特点 </h4>

- 每个节点最多有两个叶子节点
- 条件判断为假（真）的放在节点的左边
- 条件判断为真（假）的放在节点的右边

> 不是绝对说假的放在左边，真的放在右边，根据设计决定

<h4 id='2'> 2、二叉树的核心函数 </h4>

- 比较函数

	```c
	// 小于： -1
	// 等于: 0
	// 大于: 1
	typedef int (*compare_data_t)(void*, void*)
	```

- 插入核心算法

  ```c
    if (node == NULL) {
        return new Node<T>(data);
    }

    // 比较判断
    int ret = this->compare_(&data, &(node->data));
    
    // 大于0，插入到右边
    if (ret > 0) {
        node->r_child = this->_insert(node->r_child, data);
        
    // 小于0，插入到左边
    } else if (ret < 0) {
        node->l_child = this->_insert(node->l_child, data);
    }

    return node;
  ```
  
- 删除

	- 删除节点只有右节点
		
		```
		if (NULL == node->l_child) {
			Node<T>* tmp = node->r_child;
        	delete node;
        	return tmp;
    	}
		```
		
	- 删除节点只有左节点
		
		```
	    if (NULL == node->r_child) {
	        Node<T>* tmp = node->l_child;
	        delete node;
	        return tmp;
	    }
		```
		
	- 删除节点有两个节点，并且右子节点无左子节点
	
		```
	 	Node<T>* parents = node;
    	Node<T>* tmp = node->r_child;
    	
    	if (tmp->l_child == NULL) {
    		node->data = tmp->data;
    		parents->r_child = tmp->l_child
    		delete tmp;
    	}
      ```
	- 删除节点有两个节点，并且右子节点有左子节点
	
		```
	 	Node<T>* parents = node;
    	Node<T>* tmp = node->r_child;
    	
    	while (tmp->l_child != NULL) {
    		parents = tmp;
    		tmp = tmp->l_child;
    	}
    	node->data = tmp->data
    	parents->l_child = tmp->r_child
      ```

- 搜索

	```
 	int ret = this->compare_(&data, &(node->data));
	if (ret < 0) {
		this->search(node->l_child, data)
	} else {
		this->search(node->r_child, data)
	} else {
		print("find data: ", node->data)
	}
	```
