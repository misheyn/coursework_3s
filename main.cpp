#include <iostream>
#include <fstream>
#include "Tree.h"
#include "Matrix.h"

// TODO in Tree binOut needs to be fixed
// TODO check saveToBin
// TODO remove trash
// TODO need to small fix some of func

int menu();

int insert(Tree<Matrix> &tree);

int enable(Tree<Matrix> &tree);

int extract(Tree<Matrix> &tree);

int sort(Tree<Matrix> &tree);

int includeWithSort(Tree<Matrix> &tree);

int saveToBin(Tree<Matrix> &tree);

int loadFromBin(Tree<Matrix> &tree);

int main() {
    int status;
    status = menu();
    return status;
}

int menu() {
    Tree<Matrix> tree;
    Matrix arr[50];
    ifstream fileOut;
    int life = 1, ch = -1, check;

    fileOut.open("../text.txt");
    if (!fileOut.is_open()) {
        std::cerr << "File open error" << "\n";
        exit(1);
    } else {
        for (int i = 0; !fileOut.eof(); i++) {
            fileOut >> arr[i];
            tree.insertValue(&arr[i]);
        }
        fileOut.close();

        while (life) {
            cout << "Choose what you want to do:" << endl;
            cout << "[0]: Exit" << endl;
            cout << "[1]: Inserting a value into a tree" << endl;
            cout << "[2]: Enabling by logical number" << endl;
            cout << "[3]: Extract by logical number" << endl;
            cout << "[4]: Sorting" << endl;
            cout << "[5]: Inclusion with preservation of order" << endl;
            cout << "[6]: Saving string objects to a binary file" << endl;
            cout << "[7]: Loading string objects from a binary file" << endl;
            cout << "[8]: Print tree" << endl;
            cin >> ch;
            switch (ch) {
                case 0:
                    life = 0;
                    check = 0;
                    break;
                case 1:
                    check = insert(tree);
                    break;
                case 2:
                    check = enable(tree);
                    break;
                case 3:
                    check = extract(tree);
                    break;
                case 4:
                    check = sort(tree);
                    break;
                case 5:
                    check = includeWithSort(tree);
                    break;
                case 6:
                    check = saveToBin(tree);
                    break;
                case 7:
                    check = loadFromBin(tree);
                    break;
                case 8:
                    tree.printTree();
                    break;
                default:
                    if (!isdigit(ch) || isalpha(ch)) {
                        cout << "There is no such option. Enter a number between 0 and 8" << endl;
                        check = 1;
                    }
                    break;
            }
        }
    }
//    fileOut >> tree;
//    tree.printTree();
    return check;
}

int insert(Tree<Matrix> &tree) {
    int flag = 0, order = 0, k = 0, size;
    cout << "Enter the matrix in the format: first its dimension, then the matrix itself" << endl;
    cin >> order;
    auto *mtr = new Matrix(order);
    double array[order * order];
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++, k++) {
            cin >> array[k];
            mtr->SetMatrix(i, j, array[k]);
        }
    }
    size = tree.getNumberOfValues();
    tree.insertValue(mtr);
    if (size + 1 != tree.getNumberOfValues()) flag = 1;
    return flag;
}

int enable(Tree<Matrix> &tree) {
    int flag = 0, order = 0, k = 0, size, number;

    cout << "Enter the number of the tree object, instead of which you want to add a new matrix" << endl;
    cout << "Now there are " << tree.getNumberOfValues() << " objects in the tree" << endl;
    cin >> number;
    cout << "Enter the matrix in the format: first its dimension, then the matrix itself" << endl;
    cin >> order;
    auto *mtr = new Matrix(order);
    double array[order * order];
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++, k++) {
            cin >> array[k];
            mtr->SetMatrix(i, j, array[k]);
        }
    }
    size = tree.getNumberOfValues();
    tree.includeByInd(mtr, number);
    if (size + 1 != tree.getNumberOfValues()) flag = 1;
    return flag;
}

int extract(Tree<Matrix> &tree) {
    int flag = 0, size, number;

    cout << "Enter the number of the tree object you want to extract" << endl;
    cout << "Now there are " << tree.getNumberOfValues() << " objects in the tree" << endl;
    cin >> number;

    size = tree.getNumberOfValues();
    cout << "Object number " << number << endl;
    cout << tree.extractByInd(number) << endl;

    if (size - 1 != tree.getNumberOfValues()) flag = 1;
    return flag;
}

int sort(Tree<Matrix> &tree) {
    int flag = 0, size;

    size = tree.getNumberOfValues();
    tree.sortTree();

    if (size != tree.getNumberOfValues()) flag = 1;
    else cout << "Sorted\n\n";
    return flag;
}

int includeWithSort(Tree<Matrix> &tree) {
    int flag = 0, order = 0, k = 0, size;
    cout << "Enter the matrix in the format: first its dimension, then the matrix itself" << endl;
    cin >> order;
    auto *mtr = new Matrix(order);
    double array[order * order];
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++, k++) {
            cin >> array[k];
            mtr->SetMatrix(i, j, array[k]);
        }
    }
    size = tree.getNumberOfValues();
    tree.insertWithOrder(mtr);
    if (size + 1 != tree.getNumberOfValues()) flag = 1;
    return flag;
}

int saveToBin(Tree<Matrix> &tree) {
    int flag = 0, chs, order, k = 0;
    ofstream binFileIn;

    cout << "Choose what you want to do:\n"
            "write the entire tree to a file (1)\nadd new string objects (2)\n";
    cin >> chs;
    if (chs == 1) {
        binFileIn.open("../binText.dat", ios::binary);
        if (!binFileIn.is_open()) {
            std::cerr << "File open error" << "\n";
            flag = 1;
        }
        tree.saveToBin(binFileIn);
        binFileIn.close();
    } else if (chs == 2) {
        binFileIn.open("../binText.dat", ios::binary | ios::app);
        if (!binFileIn.is_open()) {
            std::cerr << "File open error" << "\n";
            flag = 1;
        }
        cout << "Enter the matrix in the format: first its dimension, then the matrix itself" << endl;
        cin >> order;
        auto *mtr = new Matrix(order);
        double array[order * order];
        for (int i = 0; i < order; i++) {
            for (int j = 0; j < order; j++, k++) {
                cin >> array[k];
                mtr->SetMatrix(i, j, array[k]);
            }
        }
//        binFileIn << *mtr << endl;
        BinaryIn(binFileIn, *mtr);
        binFileIn.close();
    }
    return flag;
}

int loadFromBin(Tree<Matrix> &tree) {
    int flag = 0;
    long long file_size;

    ifstream binFileOut;
    binFileOut.open("../binText.dat", ios::binary);
    binFileOut.seekg(0, ios::end);
    file_size = binFileOut.tellg();
    if (file_size == 0) {
        cout << "The file is empty. Save something there first\n";
        flag = 1;
    }
    if (!binFileOut.is_open()) {
        std::cerr << "File open error" << "\n";
        flag = 1;
    }
    tree.loadFromBin(binFileOut);
    binFileOut.close();

    tree.printTree();
    return flag;
}