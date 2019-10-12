#ifndef _BTREE_H_
#define _BTREE_H_

template <class T>
class BtNode {
    private:
        // an array of keys
        T* keys_;

        //minimum degree(defines the range for number of keys)
        int min_degree_;

        // and array of child pointers
        BtNode** chs_;

        // current number of keys
        int key_nums_;

        // is true when node is leaf.
        // otherwise false
        bool leaf_;

        print_t print_;

    public:
        BtNode(int t, bool leaf);
        void traverse();
        BtNode* search(int k);
};

template <class T>
BtNode<T>::BtNode(int t, bool leaf) : key_nums_(t), leaf_(leaf) {
    int k_size = (this->key_nums_<<1) - 1;
    this->keys_ = new T[k_size];
    this->chs_ = new BtNode<T>* [(this->key_nums_<<1)];
    this->key_nums_ = 0;
}


template <class T>
void BtNode<T>::traverse() {
    int i;
    for (i=0; i<n; i++) {
        if (this->leaf_ == false) {
            this->chs_[i]->traverse();
        }
        this->print_(&(this->keys_[i]));
    }

    if (this->leaf_ == false) {
        this->chs_[i]->traverse();
    }
}

template <class T>
BtNode<T>* BtNode<T>::search(int k) {
    int i = 0;
    while (i < this->key_nums_ && 
           k > this->keys_[i]) {
        i++;
    }

    if (this->keys_[i] == k) {
        return this;
    }

    if (this->leaf_ == true) {
        return NULL; 
    }

    return this->chs_[i]->search(k);
}

template <class T>
BtNode<T>* BtNode<T>::insert(int k) {
    if (NULL == this->root_) {
        this->root_ = new BtNode<T>(this->min_degree_, true);
        this->root_[0] = k;
        this->key_nums_ = 1;
    } else {
        if (this->root_->key_nums_ == (t<<1)-1) {
            BtNode

        }
    }
}

template <class T>
class Btree {
    private:
        BtNode *root_;
        int t;

    public:
        Btree(int t);
        void traverse(); BtNode* search(int k);
};


#endif
