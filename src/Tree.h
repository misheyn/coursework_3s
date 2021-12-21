#ifndef COURSEWORK_3S_TREE_H
#define COURSEWORK_3S_TREE_H

#include "TreeNode.h"
#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
class Tree {
public:
    Tree();

    ~Tree();

    void insertValue(T *data);

    void insertWithOrder(T *data);

    void printTree();

    void deleteTree();

    int getNumOfValues();

    int getNumOfTops();

    int getNumOfPeaks();

    T operator[](int i);

    void includeByInd(T *data, int i);

    T extractByInd(int i);

    void sortTree();

    ofstream &saveToBin(ofstream &os);

    ifstream &loadFromBin(ifstream &is);

private:
    TreeNode<T> *root;
    int topsCount;
    int peaksCount;
    int valueCount;

    void destructor(TreeNode<T> *);

    int addValue(TreeNode<T> **, T *);

    void createEndNode(TreeNode<T> **, T *);

    void createInterNode(TreeNode<T> *, T *, int);

    int checkNode(TreeNode<T> **, T *, int);

    void print(TreeNode<T> *);

    int lenArray(TreeNode<T> *);

    void getDepth(TreeNode<T> *, int *);

    TreeNode<T> *findInd(TreeNode<T> *, int *, int, int *);

    void sort(TreeNode<T> *);

    ofstream &binOut(ofstream &os, TreeNode<T> *node);

    void bubbleSort(TreeNode<T> **);
};

#endif //COURSEWORK_3S_TREE_H

#include "Tree.inl"