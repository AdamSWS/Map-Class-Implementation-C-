// mymap.h
//
// Adam Shaar
// mymap.h with member functions for a private template mymap class
#pragma once

#include <iostream>
#include <sstream>
#include <stack>
#include <cassert>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE *left;  // links to left child
        NODE *right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE *root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
    private:
        NODE *curr;  // points to current in-order node for begin/end

    public:
        iterator(NODE *node) {
            curr = node;
        }

        keyType operator*() {
            return curr->key;
        }

        bool operator==(const iterator &rhs) {
            return curr == rhs.curr;
        }

        bool operator!=(const iterator &rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        iterator operator++() {


            // TODO: write this function.
            if (curr->isThreaded == true) {
                curr = curr->right;
            } else {
                curr = curr->right;
                while (curr != nullptr && curr->left != nullptr) {
                    curr = curr->left;
                }
            }
            return iterator(curr);  // TODO: Update this return.
        }
    };

public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {
        // TODO: write this function.
        root = nullptr;
        size = 0;
    }

    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap(const mymap &other) {


        // TODO: write this function.
        root = _preOrderCOPY(other.root, root);
        this->size = other.size;
    }

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap &operator=(const mymap &other) {
        if (this == &other) {
            return *this;
        }
        // TODO: write this function.
        this->clear();
        root = _preOrderCOPY(other.root, root);
        this->size = other.size;
        return *this;  // TODO: Update this return.
    }

    NODE* _preOrderCOPY(NODE *otherCUR, NODE* parent ) {
        if (otherCUR == nullptr) {
            return nullptr;
        }
        NODE* newNode =  new NODE{otherCUR->key, otherCUR->value, nullptr, nullptr,
                                  otherCUR->nL, otherCUR->nR, otherCUR->isThreaded};
        newNode->left = _preOrderCOPY(otherCUR->left, newNode);
        newNode->right = (otherCUR->isThreaded) ? parent : _preOrderCOPY(otherCUR->right, parent);
        return newNode;
    }

    void _postOrderFREE(NODE *curr) {
        if (curr == nullptr) {
            return;
        } else {
            _postOrderFREE(curr->left);
            _postOrderFREE((curr->isThreaded) ? nullptr : curr->right);
            delete curr;
            curr = nullptr;
            size--;
        }
    }

    // clear:
    //
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    void clear() {


        // TODO: write this function.
        NODE *curr = root;
        _postOrderFREE(curr);
        root = nullptr;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    ~mymap() {


        // TODO: write this function.
        clear();

    }

    //
    //  :
    //
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    //
    void put(keyType key, valueType value) {
        bool exists = contains(key);
        bool broken = false;
        NODE *prev = nullptr;
        NODE *cur = root;
        NODE *parent = nullptr;
        while (cur != nullptr) {
            if (key == cur->key) {
                cur->value = value;
                return;
            }else if (key < cur->key) {
                if (exists == false) {
                    (cur->nL)++;
                }
                if ((max(cur->nL, cur->nR) > 2 * min(cur->nL, cur->nR) + 1) && broken == false) {
                    broken = true;
                    parent = prev;
                }
                prev = cur;
                cur = cur->left;
            } else {
                if (exists == false) {
                    (cur->nR)++;
                }
                if ((max(cur->nL, cur->nR) > 2 * min(cur->nL, cur->nR) + 1) && broken == false) {
                    broken = true;
                    parent = prev;
                }
                prev = cur;
                cur = (cur->isThreaded) ? nullptr : cur->right;
            }
        }
        NODE *n = new NODE();
        n->key = key;
        n->value = value;
        n->left = nullptr;
        n->right = nullptr;
        n->isThreaded = true;
        n->nL = 0;
        n->nR = 0;
        if (prev == nullptr) {
            root = n;
        } else if (key < prev->key) {
            prev->left = n;
            n->right = prev;
        } else {
            n->right = prev->right;
            prev->isThreaded = false;
            prev->right = n;
        }
        if (broken) {
            vector <NODE*> underPViolator;
            if (parent == nullptr) {
                _inorderInsert(root, underPViolator);
                root = subtreeBuild(parent, underPViolator, 0, underPViolator.size() - 1);
            } else if (n->key > parent->key) {
                _inorderInsert(parent->right, underPViolator);
                parent->right = subtreeBuild(nullptr, underPViolator, 0, underPViolator.size() - 1);
            } else {
                _inorderInsert(parent->left, underPViolator);
                parent->left =subtreeBuild(parent, underPViolator, 0, underPViolator.size() - 1);
            }
        }
        size++;
    }

    //
    // subtreeBuild
    //
    // threaads subtree to main tree
    NODE* subtreeBuild(NODE* nextInOrder, vector <NODE*>& VEC, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        int mid = (start + end) / 2;
        VEC[mid]->left = subtreeBuild(VEC[mid], VEC, start, mid-1);
        VEC[mid]->right = subtreeBuild(nextInOrder, VEC, mid + 1, end);
        if (VEC[mid]->right == nullptr) {
            VEC[mid]->right = nextInOrder;
            VEC[mid]->isThreaded = true;
        } else {
            VEC[mid]->isThreaded = false;
        }
        VEC[mid]->nL = mid - start;
        VEC[mid]->nR = end - mid;
        return VEC[mid];
    }

    //
    // _inOrder
    //
    // recursion function that saves inserts NODE*s to a vector
    void _inorderInsert( NODE* cur, vector <NODE*> &underPViolator) {
        if (cur == nullptr) {
            return;
        } else {
            _inorderInsert(cur->left, underPViolator);
            underPViolator.push_back(cur);
            _inorderInsert((cur->isThreaded) ? nullptr : cur->right, underPViolator);
        }
    }

    //
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    bool contains(keyType key) {


        // TODO: write this function.
        NODE* cur = root;
        while (cur != nullptr) {
            if (key == cur->key) {  // if the search key is equals the current node, return true
                return true;
            } else if (key < cur->key) {  // if the search key is less then the current node, go to left node
                cur = cur->left;
            } else {
                cur = (cur->isThreaded) ? nullptr : cur->right;  // if the search key is less then the current node, go to right node
            }
        }  // end of while loop

        // returns false if the nodes don't contain
        return false;  // TODO: Update this return.
    }

    //
    // get:
    //
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    valueType get(keyType key) {


        // TODO: write this function.
        NODE* cur = root;
        while (cur != nullptr) {
            if (key == cur->key) {  // if the search key is equals the current node, return true
                return cur->value;
            } else if (key < cur->key) {  // if the search key is less then the current node, go to left node
                cur = cur->left;
            } else {
                cur = (cur->isThreaded) ? nullptr : cur->right;  // if the search key is less then the current node, go to right node
            }
        }  // end of while loop

        return valueType();
    }

    //
    // operator[]:
    //
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    //
    valueType operator[](keyType key) {

        NODE* cur = root;
        while (cur != nullptr) {
            if (key == cur->key) {  // if the search key is equals the current node, returns the value of that node
                return cur->value;
            } else if (key < cur->key) {  // if the search key is less then the current node, go to left node
                cur = cur->left;
            } else {
                cur = (cur->isThreaded) ? nullptr : cur->right;  // if the search key is less then the current node, go to right node
            }
        }  // end of while loop
        put(key, valueType());
        return valueType();
    }

    //
    // Size:
    //
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    //
    int Size() {
        return size;  // returns the size
    }

    //
    // begin:
    //
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    iterator begin() {


        // TODO: write this function.
        NODE* curr = root;
        while (curr != nullptr && curr->left != nullptr) {
            curr = curr->left;
        }
        return iterator(curr);  // TODO: Update this return.
    }

    //
    // end:
    //
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    //
    // Time Complexity: O(1)
    //
    iterator end() {
        return iterator(nullptr);
    }

    void _inorder(NODE* cur, ostream& out) {
        if (cur == nullptr) {
            return;
        } else {
            _inorder(cur->left, out);
            out << "key: " << cur->key;
            out << " value: " << cur->value << endl;
            _inorder((cur->isThreaded) ? nullptr : cur->right, out);
        }
    }

    //
    // toString:
    //
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string toString() {
        // TODO: write this function.
        stringstream ss;
        _inorder(root, ss);
        return ss.str();  // TODO: Update this return.
    }

    //
    // _inOrder
    //
    // recursion function that saves map pairs to a vector of pairs
    //
    void _inorder(NODE* cur, vector<pair<keyType, valueType> >&inOrder) {
        if (cur == nullptr) {
            return;
        } else {
            _inorder(cur->left, inOrder);
            inOrder.push_back(make_pair(cur->key, cur->value));
            _inorder((cur->isThreaded) ? nullptr : cur->right, inOrder);
        }
    }

    //
    // toVector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    vector<pair<keyType, valueType> > toVector() {
        // TODO: write this function.
        vector<pair<keyType, valueType> > inorderVec;  // saves a vector of pairs from the map
        _inorder(root, inorderVec);
        return inorderVec;  // TODO: Update this return.
    }

    //
    // _preOrderString
    //
    // Prints the nodes in preorder and saves it to a string stream
    void _preOrderString(NODE* cur, ostream& ss) {
        if (cur == nullptr) {
            return;
        } else {
            ss << "key: " << cur->key <<
               ", nL: " << cur->nL  <<
               ", nR: " << cur->nR  << endl;
            _preOrderString(cur->left, ss);
            _preOrderString((cur->isThreaded) ? nullptr : cur->right, ss);
        }
    }

    //
    // checkBalance:
    //
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string checkBalance() {
        // TODO: write this function.
        stringstream ss;
        _preOrderString(root, ss);  //prints the function with pre-order recursion
        return ss.str();  // TODO: Update this return.
    }
};
