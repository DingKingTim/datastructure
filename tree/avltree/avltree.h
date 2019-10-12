#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_
#include "common.h"
#include <iostream>

#define DEBUG 0

template <class T>
class Node {
    public:
        T data;
        int height;
        Node* l_child;
        Node* r_child;

    public:
        Node(T d) : data(d), height(1), l_child(NULL), r_child(NULL) {
        }
};

template <class T>
class AvlTree {
    private:
        Node<T>* root_;
        compare_t compare_;
        print_t print_;

    public:
        AvlTree(compare_t cmp, print_t p) : compare_(cmp), print_(p), root_(NULL) {
        }

        void insert(T data);
        void del(T data);
        void preorder();
        void midorder();

    private:
        int _max(int h1, int h2);
        int _height(Node<T>* node);
        int _balance(Node<T>* node);
        Node<T>* _min_node(Node<T>* node);
        Node<T>* _right_rotate(Node<T>* node);
        Node<T>* _left_rotate(Node<T>* node);
        Node<T>* _insert(Node<T>* node, T data);
        Node<T>* _delete(Node<T>* node, T data);
        void _preorder(Node<T>* n);
        void _midorder(Node<T>* n);
};

template <class T>
int AvlTree<T>::_balance(Node<T>* node) {
    if (NULL == node) {
        return 0;
    }

    return this->_height(node->l_child) - this->_height(node->r_child);
}

template <class T>
int AvlTree<T>::_height(Node<T>* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

template <class T>
int AvlTree<T>::_max(int h1, int h2) {
    return h1 > h2 ? h1 : h2;
}

template <class T>
Node<T>* AvlTree<T>::_right_rotate(Node<T>* node) {
    Node<T>* nl = node->l_child;
    Node<T>* nlr = nl->r_child;

    nl->r_child = node;
    node->l_child = nlr;

    node->height = this->_max(this->_height(node->l_child), 
                              this->_height(node->r_child)) + 1;

    nl->height = this->_max(this->_height(nl->l_child),
                            this->_height(nl->r_child)) + 1;

    return nl;
}

template <class T>
Node<T>* AvlTree<T>::_left_rotate(Node<T>* node) {
    Node<T>* nr = node->r_child;
    Node<T>* nrl = nr->l_child;

    nr->l_child = node;
    node->r_child = nrl;

    node->height = this->_max(this->_height(node->l_child), 
                              this->_height(node->r_child)) + 1;

    nr->height = this->_max(this->_height(nr->l_child),
                            this->_height(nr->r_child)) + 1;

    return nr;
}

template <class T>
Node<T>* AvlTree<T>::_min_node(Node<T>* node) {
    if (NULL == node) {
        return node;
    }

    Node<T>* p = NULL;
    Node<T>* tmp = node;

    while (tmp != NULL) {
        p = tmp;
        tmp = p->l_child;
    }

    return p;
}

template <class T>
Node<T>* AvlTree<T>::_delete(Node<T>* node, T data) {
    if (NULL == node) {
        return node;
    }

    int ret = this->compare_(&data, &(node->data));
    if (ret < 0) {
        node->l_child = this->_delete(node->l_child, data);
    } else if (ret > 0) {
        node->r_child = this->_delete(node->r_child, data);
    } else {
        if (node->r_child == NULL || node->l_child == NULL) {
            Node<T>* child = node->l_child == NULL ?
                             node->r_child :
                             node->l_child;
            if (NULL == child) {
                delete node;
                node = NULL;
            } else {
                node->data = child->data;
                node->l_child = child->l_child;
                node->r_child = child->r_child;
                delete child;
                child = NULL;
            }
        } else {
            Node<T>* min_node = this->_min_node(node->r_child);
            node->data = min_node->data;
            node->r_child = this->_delete(node->r_child, min_node->data);
        }
    }

    if (NULL == node) {
        return NULL;
    }

    // 2> 更新删除路径上的每一个节点的高度
    node->height = 1 + this->_max(this->_height(node->l_child),
                                  this->_height(node->r_child));

    // 3> 判断删除路径上每一个节点是否达到平衡
    int balance = this->_balance(node);

#if DEBUG
    std::cout << "r_child" << node->r_child << " height: " << node->height << " balance(" << balance << ") data(" << node->data << std::endl;
#endif
    if (balance > 1 && this->_balance(node->l_child) >= 0) {
        return this->_right_rotate(node);
    }

    if (balance > 1 && this->_balance(node->l_child) < 0) {
        node->l_child = this->_left_rotate(node->l_child);
        return this->_right_rotate(node); 
    }

    if (balance < -1 && this->_balance(node->r_child) < 0) {
        return this->_right_rotate(node);
    }

    if (balance < -1 && this->_balance(node->r_child) > 0) {
        node->r_child = this->_right_rotate(node->r_child);
        return this->_left_rotate(node);
    }

    return node;
}

template <class T>
Node<T>* AvlTree<T>::_insert(Node<T>* node, T data) {
    // 旋转的原则左边的树先达到左高右底，然后右旋转
    //           右边的树先达到右高左低，然后左旋转
    //
    // 节点插入到了当前节点左子树的左边直接右旋转
    // 节点插入到了当前节点右子树的右边直接左旋转
    //
    // 节点插入到了当前节点左子树的右边导致不平衡，先左转左子节点后右转当前节点
    // 节点插入到了当前节点右子树的左边导致不平衡，先右转右子节点后左转当前节点
    //
    if (node == NULL) {
        return new Node<T>(data);
    }

    int ret = this->compare_(&(node->data), &data);
    if (ret > 0) {
        node->l_child = this->_insert(node->l_child, data);

    } else if (ret < 0) {
        node->r_child = this->_insert(node->r_child, data);

    } else {
        return node;
    }

    node->height = 1 + this->_max(this->_height(node->l_child),
                                  this->_height(node->r_child));
   
    int balance = this->_balance(node);

    // balance > 1 说明node节点的左子树比右子树高
    // data < node->l_child->data 说明由于数据插入到了左子树的左边导致
    // 树不平衡，本来是平衡的，就因为左边多插入了一个导致，所以对当前
    // 节点右旋转
    if (balance > 1 && this->compare_(&data, &(node->l_child->data)) < 0) {
        return this->_right_rotate(node);
    }

    // balance > 1 说明node节点的左子树比右子树高
    // data > node->l_child->data 说明由于数据插入到了左子树的右边导致
    // 树不平衡，本来是平衡的，就因为右边多插入了一个导致，所以对node
    // 的左节点左旋转，是的子树左高右低，然后在对当前节点右旋转
    if (balance > 1 && this->compare_(&data, &(node->l_child->data)) > 0) {
        node->l_child = this->_left_rotate(node->l_child);
        return this->_right_rotate(node);
    }

    // balance < -1 说明node节点的左子树比右子树低
    // data > node->r_child->data 说明由于数据插入到了右子树的右边导致
    // 树不平衡，本来是平衡的，就因为右边多插入了一个导致，所以对当前
    // 节点左旋转
    if (balance < -1 && this->compare_(&data, &(node->r_child->data)) > 0) {
        return this->_left_rotate(node);
    }

    // balance < -1 说明node节点的左子树比右子树低
    // data < node->r_child->data 说明由于数据插入到了右子树的右边导致
    // 树不平衡，本来是平衡的，就因为右边多插入了一个导致，所以对node
    // 的右节点右旋转，使得子树右高左低，然后在对当前节点左旋转
    if (balance < -1 && this->compare_(&data, &(node->r_child->data)) < 0) {
        node->r_child = this->_right_rotate(node->r_child);
        return this->_left_rotate(node);
    }

    return node;
}

template <class T>
void AvlTree<T>::insert(T data) {
    this->root_ = this->_insert(this->root_, data);
}

template <class T>
void AvlTree<T>::del(T data) {
    this->root_ = this->_delete(this->root_, data);
}

template <class T>
void AvlTree<T>::_preorder(Node<T>* n) {
    if (NULL == n) {
        return;
    }

    this->print_(&(n->data));
    this->_preorder(n->l_child);
    this->_preorder(n->r_child);
}

template <class T>
void AvlTree<T>::preorder() {
    this->_preorder(this->root_);
}

template <class T>
void AvlTree<T>::_midorder(Node<T>* n) {
    if (NULL == n) {
        return;
    }
    this->_midorder(n->l_child);
    this->print_(&(n->data));
    this->_midorder(n->r_child);
}

template <class T>
void AvlTree<T>::midorder() {
    this->_midorder(this->root_);
}

#endif
