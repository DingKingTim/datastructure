/*

And following do not.
Postorder and Preorder.
Preorder and Level-order.
Postorder and Level-order.
 */

#ifndef _BINARY_H_
#define _BINARY_H_
#include "queue.h"
#include "common.h"
#include <iostream>

#define TREE_DEBUG 0

typedef enum built_e {
    BuildTreeByMidAndPreOrder = 0,
    BuildTreeByMidAndPstOrder,
    BuildTreeByMidAndLvlOrder,
    BuildTreeByBSTLvlOrder,
    BuildTreeByHeapSortOrder,
} built_t;

template <class T>
class Node {

    public:
        Node(T d) : data(d), l_child(nullptr), r_child(nullptr) {}
        T data;
        Node<T>* l_child;
        Node<T>* r_child;
        Node<T>* parents;
};

template <class T>
class BinaryTree {
    public:
        // Therefore, following combination can uniquely identify a tree.
        // 1> Inorder and Preorder.
        // 2> Inorder and Postorder.
        // 3> Inorder and Level-order.
        BinaryTree(T* oth,
                   T* mid,
                   built_t t,
                   int size=0, print_t p=nullptr, compare_t c=nullptr);
        BinaryTree(T* seq, int size);
        void pre_traverse();
        void mid_traverse();
        void post_traverse();
        void breadth_traverse();
        void hknodes();
        size_t depth();
        void hknodes(int k);
        void bst_insert(T data);
        void bst_delete(T data);
        Node<T>* bst_min();
        size_t size() {return this->size_;}

    private:
        void _pre_traverse(Node<T>* n);
        void _mid_traverse(Node<T>* n);
        void _post_traverse(Node<T>* n);
        void _breadth_traverse(Node<T>* n);
        size_t _depth(Node<T>* node);
        void _hknodes(Node<T>* node, int k);
        int _search(T* mid, T data, int start, int end);
        T* _searchMidInLvl(T* mid, int start, int end, T* lvl, int len);
        Node<T>* _bst_insert(Node<T>* node, T data);
        Node<T>* _bst_delete(Node<T>* node, T data);
        Node<T>* _constructWithBstLvlOrder(Node<T> *r, T data);
        Node<T>* _constructWithHeapSortOrder(T* oth, int idx, int size);
        Node<T>* _buildTreeWithPreMidOrder(T* pre, T* mid, int start, int end);
        Node<T>* _buildTreeWithPostMidOrder(T* pst, T* mid, int start, int end);
        Node<T>* _buildTreeWithLvlMidOrder(T* lvl, T* mid, int start, int end, int len);
        Node<T>* _buildTreeWithBstLvlOrder(T* bst, int size);
        Node<T>* _buildTreeWithHeapSortOrder(T* heap, int size);

    private:
        size_t size_;
        Node<T>* root_;
        print_t print_;
        compare_t compare_;
};


template <class T>
BinaryTree<T>::BinaryTree(T* oth, T* mid, built_t t, int size, print_t p, compare_t cmp) : 
    size_(0),
    root_(nullptr),
    print_(p),
    compare_(cmp) {

    switch (t) {
    case BuildTreeByMidAndPreOrder:
        this->root_ = this->_buildTreeWithPreMidOrder(oth, mid, 0, size-1);
        break;

    case BuildTreeByMidAndPstOrder:
        this->root_ = this->_buildTreeWithPostMidOrder(oth, mid, 0, size-1);
        break;

    case BuildTreeByMidAndLvlOrder:
        this->root_ = this->_buildTreeWithLvlMidOrder(oth, mid, 0, size-1, size);
        break;

    case BuildTreeByBSTLvlOrder:
        this->root_ = this->_buildTreeWithBstLvlOrder(oth, size);
        break;

    case BuildTreeByHeapSortOrder:
        this->root_ = this->_buildTreeWithHeapSortOrder(oth, size);
        break;

    default:
        throw "Unknow built type";
    }
}

template <class T>
Node<T>* BinaryTree<T>::_constructWithBstLvlOrder(Node<T> *r, T data) {

    if (r == nullptr) {
        return new Node<T>(data);
    }

    if (this->compare_(&(r->data), &data) <= 0) {
        r->r_child = this->_constructWithBstLvlOrder(r->r_child, data);
    } else {
        r->l_child = this->_constructWithBstLvlOrder(r->l_child, data);
    }

    return r;
}

template <class T>
Node<T>* BinaryTree<T>::_buildTreeWithBstLvlOrder(T* bst, int size) {
    Node<T>* root = nullptr;

    for (int i=0; i<size; i++) {
        root = this->_constructWithBstLvlOrder(root, bst[i]);
    }
    return root;
}

template <class T>
Node<T>* BinaryTree<T>::_constructWithHeapSortOrder(T* oth, int idx, int size) {
    if (idx > size) {
        return nullptr;
    }

    Node<T>* node = new Node<T>(oth[idx-1]);
    if (idx == size) {
        return node;
    }

    node->l_child = this->_constructWithHeapSortOrder(oth, idx<<1, size);
    node->r_child = this->_constructWithHeapSortOrder(oth, 1+(idx<<1), size);

    return node;
}

template <class T>
Node<T>* BinaryTree<T>::_buildTreeWithHeapSortOrder(T* oth, int size) {
    return this->_constructWithHeapSortOrder(oth, 1, size);
}

template <class T>
Node<T>* BinaryTree<T>::_buildTreeWithPreMidOrder(T* pre, T* mid, int start, int end) {
    static int index = 0;

    if (start > end) {
        return nullptr;
    }

    // 1> pick and element from pre order and then create new node
    // 2> increment index to pick next element in next recursive call
    Node<T>* node = new Node<T>(pre[index++]);
    if (start == end) {
        this->size_ += 1;
        return node;
    }

    // 3> find index of new node in mid order, we call this index as mid-index
    int midIndex = this->_search(mid, node->data, start, end);

    // 4> call _buildTreeWithPreMidOrder for elements before mid-index and make 
    //    built tree as left subtree of new node
    node->l_child = this->_buildTreeWithPreMidOrder(pre, mid, start, midIndex-1);

    // 5> call _buildTreeWithPreMidOrder for elements after mid-index and make 
    //    built tree as right subtree of new node
    node->r_child = this->_buildTreeWithPreMidOrder(pre, mid, midIndex+1, end);

    this->size_ += 1;

#if TREE_DEBUG
    std::cout << "node: " << node->data;
    if (nullptr != node->l_child) std::cout << " l-child: " << node->l_child->data;
    if (nullptr != node->r_child) std::cout << " r-child: " << node->r_child->data;
    std::cout << std::endl;
#endif
    return node;
}


template <class T>
Node<T>* BinaryTree<T>::_buildTreeWithPostMidOrder(T* pst, T* mid, int start, int end) {
    static int index = end;

    if (end < start) {
        return nullptr;
    }

    // 1> root node is last node in post-order, we call it root-node
    //    be care for index
    Node<T>* node = new Node<T>(pst[index--]);

    if (end == start) {
        this->size_++;
        return node;
    }

    // 2> search root-node's index in mid-order
    int midIndex = this->_search(mid, node->data, start, end);

    // 3> the right side nodes in mid-order of root-node is it's right child
    node->r_child = this->_buildTreeWithPostMidOrder(pst, mid, midIndex+1, end);

    // 4> the left side nodes in mid-order of root-node is it's left child
    node->l_child = this->_buildTreeWithPostMidOrder(pst, mid, start, midIndex-1);

    this->size_++;
    return node;
}

template <class T>
Node<T>* BinaryTree<T>::_buildTreeWithLvlMidOrder(T* lvl, T* mid, int start, int end, int len) {
    if (start > end) {
        return nullptr;
    }

#if TREE_DEBUG
    std::cout << std::endl << "0. lvl-len " << len << ", " << "mid (" << start << " ," << end << "): ";

    for (int k=0; k<len; k++) {
        std::cout << lvl[k] << " ";
    }
    std::cout << std::endl;
#endif

    // 1> first node of lvl-order is root
    Node<T> *node = new Node<T>(lvl[0]);
    if (start == end) {
        this->size_++;
        return node;
    }

    // find out root-node position in mid-order sequence
    // 2> the left nodes of root-node in mid-order is left subtree
    // 3> the right nodes of root-node in mid-order is right subtree
    int rootIdxInMid = this->_search(mid, node->data, start, end);

#if TREE_DEBUG
    std::cout << "1.--found mid(" << start << " ," << end << "), " << rootIdxInMid << " : " << node->data << std::endl;
#endif
    int l_lvl_size = rootIdxInMid - start;
    int r_lvl_size = end - rootIdxInMid;


    // 4> after sep 2>, find out left nodes's position in lvl-order and create
    //    new lvl-order, we call it 'l_lvl'
    T* l_lvl = this->_searchMidInLvl(mid, start, rootIdxInMid-1, lvl, len);
#if TREE_DEBUG
    std::cout << "2. l-lv-size (" << start << ", " << (rootIdxInMid-1) << "):  ";
    for (int k=0; k<l_lvl_size; k++) {
        std::cout << l_lvl[k] << " ";
    }
    std::cout << std::endl;
#endif

    // 5> after sep 2>, find out right nodes's position in lvl-order and create
    //    new lvl-order, we call it 'r_lvl'
    T* r_lvl = this->_searchMidInLvl(mid, rootIdxInMid + 1, end, lvl, len);
#if TREE_DEBUG
    std::cout << "3. r-lv-size: " << r_lvl_size << " (" << rootIdxInMid << ", " << end << ") ";
    for (int k=0; k<r_lvl_size; k++) {
        std::cout << r_lvl[k] << " ";
    }
    std::cout << std::endl;
#endif

    if (nullptr != l_lvl) {
        node->l_child = this->_buildTreeWithLvlMidOrder(l_lvl, mid, start, rootIdxInMid-1, l_lvl_size);
        delete [] l_lvl;
    }

    if (nullptr != r_lvl) {
        node->r_child = this->_buildTreeWithLvlMidOrder(r_lvl, mid, rootIdxInMid+1, end, r_lvl_size);
        delete [] r_lvl;
    }

    this->size_++;
    return node;
}

template <class T>
T* BinaryTree<T>::_searchMidInLvl(T* mid, int start, int end, T* lvl, int len) {
    if (start > end) {
        return nullptr;
    }

    int j = 0;
    int range = end - start + 1;
    T* new_lvl = new T[range];
   
    // care: keep lvl-order's order
    //       if lvl-order's node in mid, insert new lvl-order.
    for (int i=0; i<len; i++) {
        int lvl_idx = this->_search(mid, lvl[i], start, end);
        if (lvl_idx != -1) {
            new_lvl[j++] = lvl[i];
        }
    }

    return new_lvl;
}

template <class T>
int BinaryTree<T>::_search(T* mid, T data, int start, int end) {
    for (int i=start; i<=end; i++) {
        int ret = this->compare_(&(mid[i]), &data);
        if (0 == ret) {
            return i;
        }
    }

    return -1;
}


template <class T>
void BinaryTree<T>::_pre_traverse(Node<T>* node) {
    if (node == nullptr) {
        return;
    }

    this->print_(node);
    this->_pre_traverse(node->l_child);
    this->_pre_traverse(node->r_child);
}

template <class T>
void BinaryTree<T>::_mid_traverse(Node<T>* node) {
    if (node == nullptr) {
        return;
    }
    
    this->_mid_traverse(node->l_child);
    this->print_(node);
    this->_mid_traverse(node->r_child);
}

template <class T>
void BinaryTree<T>::_post_traverse(Node<T>* node) {
    if (node == nullptr || node == NULL) {
        return;
    }
    
    this->_post_traverse(node->l_child);
    this->_post_traverse(node->r_child);
    this->print_(node);
}


template <class T>
void BinaryTree<T>::_breadth_traverse(Node<T>* n) {
    Queue<Node<T>*, 6> q;
    q.put(n);

    while (!q.empty()) {

        Node<T>* pn = q.get();
        this->print_(pn);

        if (pn->l_child != nullptr) {
            q.put(pn->l_child);
        }

        if (pn->r_child != nullptr) {
            q.put(pn->r_child);
        }
    }
}

template <class T>
void BinaryTree<T>::pre_traverse() {
    this->_pre_traverse(this->root_);
}

template <class T>
void BinaryTree<T>::mid_traverse() {
    this->_mid_traverse(this->root_);
}

template <class T>
void BinaryTree<T>::post_traverse() {
    this->_post_traverse(this->root_);
}

template <class T>
void BinaryTree<T>::breadth_traverse() {
    this->_breadth_traverse(this->root_);
}

template <class T>
size_t BinaryTree<T>::_depth(Node<T>* node) {
    if (nullptr == node) {
        return 0;
    }

    size_t l_depth = _depth(node->l_child);
    size_t r_depth = _depth(node->r_child);

    return l_depth > r_depth ? l_depth + 1 : r_depth + 1;
}

template <class T>
size_t BinaryTree<T>::depth() {
    return this->_depth(this->root_);
}

template <class T>
void BinaryTree<T>::_hknodes(Node<T>* node, int k) {
    if (nullptr == node) {
        return;
    }

    if (0 == k) {
        this->print_(&(node->data));
        return;
    }

    this->_hknodes(node->l_child, k-1);
    this->_hknodes(node->r_child, k-1);
}

template <class T>
void BinaryTree<T>::hknodes(int k) {
    this->_hknodes(this->root_, k);
}

template <class T>
Node<T>* BinaryTree<T>::_bst_insert(Node<T>* node, T data) {
    if (node == nullptr) {
        return new Node<T>(data);
    }

    if (0 < this->compare_(&(node->data), &data)) {
        node->r_child = this->_bst_insert(node->r_child, data);
    } else {
        node->l_child = this->_bst_insert(node->l_child, data);
    }

    return node;
}

template <class T>
Node<T>* BinaryTree<T>::_min_node(Node<T>* node) {
    Node<T>* p = nullptr;
    Node<T>* tmp = node;
    while (nullptr != tmp) {
        p = tmp;
        tmp = tmp->l_child;
    }

    return p;
}

template <class T>
Node<T>* BinaryTree<T>::_bst_delete(Node<T>* node, T data) {
    
    if (node == nullptr) {
        return node;
    }

    int ret = this->compare_(&(node->data), &data);

    if (ret > 0) {
        this->_bst_delete(node->r_child, data);
        return node;
    }

    if (ret < 0) {
        this->_bst_delete(node->l_child, data);
        return node;
    }

    // 1> node has only one child
    if (nullptr == node->l_child) {
        Node<T>* tmp = node->r_child;
        delete node;
        return tmp;
    }

    // 2> node has only one child
    if (nullptr == node->r_child) {
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
    Node<T>* parents = nullptr;
    Node<T>* tmp = node->r_child;
    while (tmp->l_child != nullptr) {
        parents = tmp;
        tmp = tmp->l_child;
    }
    node->data = tmp->data;
    parents->r_child = tmp->r_child;
    delete tmp;

    return node;
}

template <class T>
void BinaryTree<T>::bst_insert(T data) {
    this->_bst_insert(this->root_, data);
}

template <class T>
void BinaryTree<T>::bst_delete(T data) {
    this->root_ = this->_bst_delete(this->root_, data);
}

template <class T>
Node<T>* BinaryTree<T>::bst_min() {
    Node<T>* min_node = nullptr; 
    Node<T>* tmp = this->root_;

    while (tmp != nullptr) {
        min_node = tmp;
        tmp = tmp->l_child;
    }

    return min_node;
}

template <class T>
bool _same_tree_order(T* pst, T* pre, T* mid, int size, compare_t cmp) {

    // 1> size=0, all of them are equal
    if (size == 0) {
        return true;
    }

    // 2> size=1, just compare position 0 value
    if (size == 1) {
        return (0 == cmp(&(pst[0]), &(mid[0])) &&
                0 == cmp(&(mid[0]), &(pre[0])));
    }

    // 3> find pre-order[0] in mid-order
    int idx = -1;
    for (int i=0; i<size; i++) {
        if (0 == cmp(&(pre[0]), &(mid[i]))) {
            idx = i;
            break;
        }
    }

    // 4> not found, obviously not same order
    if (idx == -1) {
        return false;
    }

    // 5> left subtree check, 0~idx of mid become pre-order and post-order's
    //    left subtree
    bool ret1 = _same_tree_order(pst, pre+1, mid, idx, cmp);

    // 6> right subtree check, (idx+1, size-idx-1) of mid-order become pre-order
    //    and post-order's right subtree
    bool ret2 = _same_tree_order(pst+idx, pre+idx+1, mid+idx+1, size-idx-1, cmp);

    return (ret1 && ret2);
}

template <class T>
bool same_tree_order(T* pst, T* pre, T* mid, int size, compare_t cmp) {
    return _same_tree_order(pst, pre, mid, size, cmp); 
}

#endif
