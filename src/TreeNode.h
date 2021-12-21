#pragma once
#ifndef COURSEWORK_3S_TREENODE_H
#define COURSEWORK_3S_TREENODE_H

#include "Matrix.h"

#define N 3

template<typename T>
class TreeNode {

public:
    TreeNode();

    T *obj[N + 1];
    int count;
    TreeNode<T> *left;
    TreeNode<T> *right;
};

#endif //COURSEWORK_3S_TREENODE_H
#include "TreeNode.inl"
