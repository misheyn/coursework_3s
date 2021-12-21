#pragma once

#include "Tree.h"

template<typename T>
Tree<T>::Tree() {
    root = nullptr;
    topsCount = 0;
    peaksCount = 0;
    valueCount = 0;
}

template<typename T>
Tree<T>::~Tree() {
    destructor(root);
}

template<typename T>
void Tree<T>::getDepth(TreeNode<T> *node, int *n) {
    if (node != nullptr) {
        (*n)++;
        getDepth(node->left, n);
    }
}

template<typename T>
int Tree<T>::lenArray(TreeNode<T> *node) {
    int i = 0;
    if (node != nullptr) {
        while (node->obj[i] != nullptr) {
            i++;
        }
    }
    return i;
}

template<typename T>
void Tree<T>::destructor(TreeNode<T> *node) {
    if (node != nullptr) {
        destructor(node->left);
        destructor(node->right);

        delete node;
    }
}

template<typename T>
void Tree<T>::insertValue(T *data) {
    addValue(&root, data);
    valueCount++;
}

template<typename T>
void Tree<T>::insertWithOrder(T *data) {
    addValue(&root, data);
    sort(root);
    valueCount++;
}

template<typename T>
int Tree<T>::addValue(TreeNode<T> **node, T *data) {
    int check = 1;
    if (checkNode(node, data, 0)) {
    } else if (checkNode(&(*node)->left, data, 1)) {
    } else if (checkNode(&(*node)->right, data, 2)) {
    } else if (addValue(&(*node)->left, data)) {
    } else if (addValue(&(*node)->right, data)) {
    } else { check = 0; }
    return check;

}

template<typename T>
int Tree<T>::checkNode(TreeNode<T> **node, T *data, int st) {
    int check = 1;
    int len;
    TreeNode<T> *tmp = *node;
    if (tmp == nullptr) {
        createEndNode(&tmp, data);
    } else if (lenArray(tmp) < N && tmp->count == 0) {
        len = lenArray(tmp);
        tmp->obj[len] = data;
        tmp->obj[len + 1] = nullptr;
    } else if (tmp->left == nullptr) {
        createInterNode(tmp, data, st);
    } else if (lenArray(tmp->right) < N && tmp->right->count == 0) {
        len = lenArray(tmp->right);
        tmp->right->obj[len] = data;
        tmp->right->obj[len + 1] = nullptr;
    } else {
        check = 0;
    }
    *node = tmp;
    return check;
}

template<typename T>
void Tree<T>::createInterNode(TreeNode<T> *node, T *data, int st) {
    auto *newNode = new TreeNode<T>;
    topsCount++;

    for (int i = 0; i < lenArray(node) + 1; ++i) {
        newNode->obj[i] = node->obj[i];

    }
    int len = lenArray(node);
    for (int i = 0; i < len + 1; ++i) {
        node->obj[i] = nullptr;
    }
    int n = 0, m = 0;
    if (st == 2) {
        getDepth(root, &n);
        getDepth(node, &m);
        node->count = n - m;
    } else node->count = n - m + 1;

    node->left = newNode;
    createEndNode(&node->right, data);

}

template<typename T>
void Tree<T>::createEndNode(TreeNode<T> **node, T *val) {
    peaksCount++;
    *node = new TreeNode<T>;
    int len = lenArray(*node);
    (*node)->obj[len] = val;
    (*node)->obj[len + 1] = nullptr;
}

template<typename T>
void Tree<T>::printTree() {
    print(root);
}

template<typename T>
void Tree<T>::deleteTree() {
    delete root;
    root = nullptr;
    valueCount = 0;
    topsCount = 0;
    peaksCount = 0;
}

template<typename T>
void Tree<T>::print(TreeNode<T> *node) {
    if (node != nullptr) {
        for (int i = 0; i < N && node->count == 0; ++i) {
            if (node->obj[i] != nullptr) {
                cout << *(node->obj[i]) << endl;
            } else {
                cout << nullptr << endl;
            }
            if (i == N - 1) cout << endl << endl;
        }
        print(node->left);
        print(node->right);
    }
}

template<typename T>
int Tree<T>::getNumOfValues() {
    return valueCount;
}

template<typename T>
int Tree<T>::getNumOfTops() {
    return topsCount;
}

template<typename T>
int Tree<T>::getNumOfPeaks() {
    return peaksCount;
}

template<typename T>
TreeNode<T> *Tree<T>::findInd(TreeNode<T> *node, int *curI, int needI, int *ind) {
    int n = -1;
    if (node == nullptr) {
        return nullptr;
    }

    while (node->obj[++n] != nullptr) {
        if (*curI == needI) {
            *ind = n;
            return node;
        }
        (*curI)++;
    }

    TreeNode<T> *tmp = findInd(node->left, curI, needI, ind);
    if (!tmp)
        tmp = findInd(node->right, curI, needI, ind);
    return tmp;
}

template<typename T>
T Tree<T>::operator[](int i) {
    int tmp = 0, pos = 0;
    TreeNode<T> *node = findInd(root, &tmp, i, &pos);
    return *(node->obj[pos]);
}

template<typename T>
void Tree<T>::includeByInd(T *data, int i) {
    int tmp = 0, pos = 0;
    TreeNode<T> *node = findInd(root, &tmp, i, &pos);
    node->obj[pos] = data;
}

template<typename T>
T Tree<T>::extractByInd(int i) {
    int tmp = 0, pos = 0;
    TreeNode<T> *node = findInd(root, &tmp, i, &pos);
    T obj = *(node->obj[pos]);
    node->obj[pos] = nullptr;
    return obj;
}

template<typename T>
void Tree<T>::sortTree() {
    sort(root);
}

template<typename T>
void Tree<T>::sort(TreeNode<T> *node) {
    if (node != nullptr) {
        if (node->count != 0 && (lenArray(node->right) > 0 || lenArray(node->left) > 0)) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (node->left->obj[i] != nullptr && node->right->obj[j] != nullptr) {
                        if (*(node->right->obj[j]) < *(node->left->obj[i]))
                            swap(*(node->right->obj[j]), *(node->left->obj[i]));
                    } else {
                        if (node->left->obj[i] == nullptr && node->right->obj[j] != nullptr) {
                            T *obj;
                            obj = node->right->obj[j];
                            node->left->obj[i] = obj;
                            node->right->obj[j] = nullptr;
                        }
                    }
                }
            }
            bubbleSort(&(node->left));
            bubbleSort(&(node->right));
        } else {
            if (lenArray(node->right) == 0 && lenArray(node->left) != 0)
                bubbleSort(&(node->left));
        }
        sort(node->left);
        sort(node->right);
    }
}

template<typename T>
void Tree<T>::bubbleSort(TreeNode<T> **node) {
    TreeNode<T> *tmp = *node;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (tmp->obj[j] != nullptr && tmp->obj[j + 1] != nullptr) {
                if (*(tmp->obj[j + 1]) < *(tmp->obj[j]))
                    swap(*(tmp->obj[j + 1]), *(tmp->obj[j]));
            } else {
                if (tmp->obj[j] == nullptr && tmp->obj[j + 1] != nullptr) {
                    T *obj;
                    obj = tmp->obj[j + 1];
                    tmp->obj[j] = obj;
                    tmp->obj[j + 1] = nullptr;
                }
            }
        }
    }
    *node = tmp;
}

template<typename T>
ofstream &Tree<T>::saveToBin(ofstream &os) {
    binOut(os, root);
    return os;
}

template<typename T>
ifstream &Tree<T>::loadFromBin(ifstream &is) {
    deleteTree();
    is.seekg(0, ios::end);
    long long size = is.tellg();
    is.seekg(0, ios::beg);

    while (is.tellg() != size) {
        auto *matrix = new Matrix;
        BinaryIn(is, *matrix);
        addValue(&root, matrix);
        valueCount++;
    }
    return is;
}

template<typename T>
ofstream &Tree<T>::binOut(ofstream &os, TreeNode<T> *node) {
    if (node != nullptr) {
        for (int i = 0; i < lenArray(node); i++) {
            BinaryOut(os, *node->obj[i]);
        }
        binOut(os, node->left);
        binOut(os, node->right);
    }
    return os;
}
