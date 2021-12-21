#pragma once
#include "TreeNode.h"

template<typename T>
TreeNode<T>::TreeNode() {
    right = left = nullptr;
    count = 0;
    for (auto &i: obj) {
        i = nullptr;
    }
}

