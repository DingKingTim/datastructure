#ifndef _BST_TREE_H_
#define _BST_TREE_H_
#include "common.h"
#include <iostream>

#define TREE_DEBUG 0

template <class T>
class Node {

    public:
        Node(T d) : data(d), l_child(NULL), r_child(NULL) {}
        T data;
        Node<T>* l_child;
        Node<T>* r_child;
        Node<T>* parents;
};

template <class T>
class BstTree {
    public:
        BstTree(print_t p=NULL, compare_t c=NULL);

        void preorder();
        void midorder();
        void pstorder();

        void insert(T data);
        void del(T data);

    private:
        void _preorder(Node<T>* n);
        void _midorder(Node<T>* n);
        void _pstorder(Node<T>* n);
        
        Node<T>* _min_node(Node<T>* node);
        Node<T>* _insert(Node<T>* node, T data);
        Node<T>* _delete(Node<T>* node, T data);

    private:
        Node<T>* root_;
        print_t print_;
        compare_t compare_;
};


template <class T>
BstTree<T>::BstTree(print_t p, compare_t cmp) : 
    root_(NULL), print_(p), compare_(cmp) {
}

template <class T>
void BstTree<T>::_preorder(Node<T>* node) {
    if (node == NULL) {
        return;
    }

    this->print_(node);
    this->_preorder(node->l_child);
    this->_preorder(node->r_child);
}

template <class T>
void BstTree<T>::_midorder(Node<T>* node) {
    if (node == NULL) {
        return;
    }
    
    this->_midorder(node->l_child);
    this->print_(node);
    this->_midorder(node->r_child);
}

template <class T>
void BstTree<T>::_pstorder(Node<T>* node) {
    if (node == NULL || node == NULL) {
        return;
    }
    
    this->_pstorder(node->l_child);
    this->_pstorder(node->r_child);
    this->print_(node);
}


template <class T>
void BstTree<T>::preorder() {
    this->_preorder(this->root_);
}

template <class T>
void BstTree<T>::midorder() {
    this->_midorder(this->root_);
}

template <class T>
void BstTree<T>::pstorder() {
    this->_pstorder(this->root_);
}

template <class T>
Node<T>* BstTree<T>::_min_node(Node<T>* node) {
    Node<T>* p = NULL;
    Node<T>* tmp = node;
    while (NULL != tmp) {
        p = tmp;
        tmp = tmp->l_child;
    }

    return p;
}

template <class T>
Node<T>* BstTree<T>::_insert(Node<T>* node, T data) {
    
    if (node == NULL) {
        return new Node<T>(data);
    }

    int ret = this->compare_(&data, &(node->data));
    if (ret > 0) {
        node->r_child = this->_insert(node->r_child, data);
    } else if (ret < 0) {
        node->l_child = this->_insert(node->l_child, data);
    }

    return node;
}

template <class T>
Node<T>* BstTree<T>::_delete(Node<T>* node, T data) {
    
    if (node == NULL) {
        return node;
    }

    int ret = this->compare_(&data, &(node->data));

    if (ret > 0) {
        node->r_child = this->_delete(node->r_child, data);
        return node;
    }

    if (ret < 0) {
        node->l_child = this->_delete(node->l_child, data);
        return node;
    }

    // 1> node has only one child
    if (NULL == node->l_child) {
        Node<T>* tmp = node->r_child;
        delete node;
        return tmp;
    }

    // 2> node has only one child
    if (NULL == node->r_child) {
        Node<T>* tmp = node->l_child;
        delete node;
        return tmp;
    }

#if 0
       
    // 3> r_child > l_child, so found out min node in r_child,
    Node<T>* min_node = this->_min_node(node->r_child);

    // 4> delete node's data replace with min_node data, ant it
    //    promise bigger than node->r_child
    node->data = min_node->data;

    // 5> delete min_node
    node->r_child = this->_bst_delete(node->r_child, min_node->data);
#endif
    // 3> track parents avoid delete recursion
    Node<T>* parents = node;
    Node<T>* tmp = node->r_child;

    while (tmp->l_child != NULL) {
        parents = tmp;
        tmp = tmp->l_child;
    }
    node->data = tmp->data;
    parents->l_child = tmp->r_child;
    delete tmp;

    return node;
}

template <class T>
void BstTree<T>::insert(T data) {
    this->root_ = this->_insert(this->root_, data);
}

template <class T>
void BstTree<T>::del(T data) {
    this->root_ = this->_delete(this->root_, data);
}

#endif
