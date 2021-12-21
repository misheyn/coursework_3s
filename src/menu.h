#ifndef COURSEWORK_3S_MENU_H
#define COURSEWORK_3S_MENU_H

#include "Matrix.h"
#include "Tree.h"

int menu();

int insert(Tree <Matrix> &tree);

int enable(Tree <Matrix> &tree);

int extract(Tree <Matrix> &tree);

int sort(Tree <Matrix> &tree);

int includeWithSort(Tree <Matrix> &tree);

int saveToBin(Tree <Matrix> &tree);

int loadFromBin(Tree <Matrix> &tree);

void ignoreChars(int &status);

#endif //COURSEWORK_3S_MENU_H
