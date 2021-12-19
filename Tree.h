#ifndef COURSEWORK_3S_TREE_H
#define COURSEWORK_3S_TREE_H

#include "TreeNode.h"
#include <iostream>

using namespace std;

template<typename T>
class Tree {
public:
    Tree() : root(nullptr), topsCount(0), valueCount(0) {}

    ~Tree() {
        destructor(root);
    }

    void insertValue(T *data);

    void insertWithOrder(T *data);

    void printTree();

    int getNumberOfValues();

    T operator[](int i);

    void includeByInd(T *data, int i);

    T extractByInd(int i);

    void sortTree();

    ofstream &saveToBin(ofstream &os);

    ifstream &loadFromBin(ifstream &is);

//    template<typename T1>
//    friend istream &operator>>(istream &, Tree<T1> *);

private:
    TreeNode<T> *root;
    int topsCount;
    int valueCount;

    void destructor(TreeNode<T> *);

    int addValue(TreeNode<T> **, T *);

    void createEndNode(TreeNode<T> **, T *);

    void createInterNode(TreeNode<T> *, T *, int);

    int checkNode(TreeNode<T> **, T *, int);

    void print(TreeNode<T> *node);

    int lenArray(TreeNode<T> *node);

    int getDepth(TreeNode<T> *node);

    void findDepth(TreeNode<T> *node, int *n);

    void printSt(TreeNode<T> *node);

    TreeNode<T> *findInd(TreeNode<T> *node, int *curI, int needI, int *ind);

    void sort(TreeNode<T> *node);

    ofstream &binIn(ofstream &os, TreeNode<T> *node);

    ifstream &binOut(ifstream &is, TreeNode<T> *node);

    void bubbleSort(TreeNode<T> **node);
};

template<typename T>
int Tree<T>::getDepth(TreeNode<T> *node) {
    int depth = 0;

    findDepth(node, &depth);

    return depth;
}

template<typename T>
void Tree<T>::findDepth(TreeNode<T> *node, int *n) {
    if (node != nullptr) {
        (*n)++;
        findDepth(node->left, n);
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
    } else
        /*if (checkNode(&(*node)->left->left, data)) {
        } else if (checkNode(&(*node)->left->right, data)) {
        } else if (checkNode(&(*node)->right->left, data)) {
        } else if (checkNode(&(*node)->right->right, data)) {
        } else {*/
    if (addValue(&(*node)->left, data)) {
    } else if (addValue(&(*node)->right, data)) {
    } else { check = 0; }
//        }
//    }
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

//    topsCount++;
    for (int i = 0; i < lenArray(node) + 1; ++i) {
        newNode->obj[i] = node->obj[i];

    }
    int len = lenArray(node);
    for (int i = 0; i < len + 1; ++i) {
        node->obj[i] = nullptr;
    }

    if (st == 2)
        node->count = getDepth(root) - getDepth(node);
    else node->count = getDepth(root) - getDepth(node) + 1;

    node->left = newNode;
    createEndNode(&node->right, data);

}

template<typename T>
void Tree<T>::createEndNode(TreeNode<T> **node, T *val) {
    topsCount++;
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
void Tree<T>::print(TreeNode<T> *node) {
    if (node != nullptr) {
        for (int i = 0; i < N && node->count == 0; ++i) {
            if (node->obj[i] != nullptr) {
                cout << *(node->obj[i]);
            } else {
                cout << "nullptr\n";
            }
            cout << endl << endl;
        }
        print(node->left);
        print(node->right);
    }
}

template<typename T>
int Tree<T>::getNumberOfValues() {
    return valueCount;
}

template<typename T>
void Tree<T>::printSt(TreeNode<T> *node) {
    if (node != nullptr) {
        if ((node->count) > 0)
            cout << (node->count) << endl;

        printSt(node->left);
        printSt(node->right);
    }

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

/*template<typename T>
istream &operator>>(istream &is, Tree<T> *tree) {
    T arr[100];
    int i = 0;
    while (!is.eof()) {
        is >> arr[i];
        (*tree).insertValue(&arr[i]);
//    tree.printTree();
        i++;
    }
    return is;
}*/

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
        if (node->count != 0 && lenArray(node->right) > 0 && lenArray(node->left) > 0) {
            int len1 = lenArray(node->left);
            int len2 = lenArray(node->right);
            for (int i = 0; i < len1; i++) {
                for (int j = 0; j < len2; j++) {
                    if (*(node->right->obj[j]) < *(node->left->obj[i])) {
                        swap(*(node->right->obj[j]), *(node->left->obj[i]));
                    }
                }
            }
            bubbleSort(&(node->left));
            bubbleSort(&(node->right));
        } else {
            if (lenArray(node->right) == 0)
                bubbleSort(&(node->left));
        }
        sort(node->left);
        sort(node->right);
    }
}

template<typename T>
void Tree<T>::bubbleSort(TreeNode<T> **node) {
    for (int i = 0; i < lenArray(*node) - 1; i++) {
        for (int j = 0; j < lenArray(*node) - i - 1; j++) {
            if (*((*node)->obj[j + 1]) < *((*node)->obj[j])) {
                swap(*((*node)->obj[j + 1]), *((*node)->obj[j]));
            }
        }
    }
}

template<typename T>
ofstream &Tree<T>::saveToBin(ofstream &os) {
    binIn(os, root);
    return os;
}

template<typename T>
ifstream &Tree<T>::loadFromBin(ifstream &is) {
    binOut(is, root);
    return is;
}

template<typename T>
ofstream &Tree<T>::binIn(ofstream &os, TreeNode<T> *node) {
    if (node != nullptr) {
            for (int i = 0; i < lenArray(node); ++i) {
//                if (node->obj[i] != nullptr)
                    os.write((char *) &*(node->obj[i]), sizeof(double));
            }
        binIn(os, node->left);
        binIn(os, node->right);
    }
    return os;
}

template<typename T>
ifstream &Tree<T>::binOut(ifstream &is, TreeNode<T> *node) {

    while (!is.eof()) {
//        is.read((char *) &*(node->obj[i]), sizeof(double));
    }
    if (node != nullptr) {
            for (int i = 0; i < lenArray(node); ++i) {
                if (node->obj[i] != nullptr)
                    is.read((char *) &*(node->obj[i]), sizeof(double));
            }
        binOut(is, node->left);
        binOut(is, node->right);
    }
    return is;
}


#endif //COURSEWORK_3S_TREE_H
