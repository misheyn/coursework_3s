#include "menu.h"

int menu() {
    Tree<Matrix> tree;
    Matrix arr[50];
    ifstream fileIn;
    int life = 1, ch = -1, check = 0;

    fileIn.open("../datasets/text.txt");
    if (!fileIn.is_open()) {
        std::cerr << "! File open error" << "\n";
        exit(1);
    } else {
        for (int i = 0; !fileIn.eof(); i++) {
            fileIn >> arr[i];
            tree.insertValue(&arr[i]);
        }
        fileIn.close();

        while (life) {
            cout << "*********************************************" << endl;
            cout << "*  " << "Choose what you want to do:" << endl;
            cout << "*  " << "[0]: Exit" << endl;
            cout << "*  " << "[1]: Inserting a value into a tree" << endl;
            cout << "*  " << "[2]: Enabling by logical number" << endl;
            cout << "*  " << "[3]: Extract by logical number" << endl;
            cout << "*  " << "[4]: Sorting" << endl;
            cout << "*  " << "[5]: Inclusion with preservation of order" << endl;
            cout << "*  " << "[6]: Saving string objects to a binary file" << endl;
            cout << "*  " << "[7]: Loading string objects from a binary file" << endl;
            cout << "*  " << "[8]: Print tree" << endl;
            cout << "*  " << "[9]: Print tree statistics" << endl;
            cout << "*  " << "[10]: Remove tree" << endl;
            cin >> ch;
            ignoreChars(ch);
            switch (ch) {
                case 0:
                    life = 0;
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
                case 9:
                    cout << "Number of objects in the tree: " << tree.getNumOfValues() << endl;
                    cout << "Number of intermediate tops: " << tree.getNumOfTops() << endl;
                    cout << "Number of end tops: ";
                    cout << tree.getNumOfPeaks() << endl;
                    break;
                case 10:
                    tree.deleteTree();
                    break;
                default:
                    cout << "! Error. There is no such option. ";
                    cout << "Please enter a number between 0 and 10\n\n";
                    break;
            }
        }
    }
    return check;
}

int insert(Tree<Matrix> &tree) {
    int flag = 0, order = 0, k = 0, size;
    cout << "Type the square matrix in the format: at first its dimension (one number), then the matrix itself\n";
    cin >> order;
    auto *mtr = new Matrix(order);
    double array[order * order];
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++, k++) {
            cin >> array[k];
            mtr->setMatrix(i, j, array[k]);
        }
    }
    size = tree.getNumOfValues();
    tree.insertValue(mtr);
    if (size + 1 != tree.getNumOfValues()) flag = 1;
    return flag;
}

int enable(Tree<Matrix> &tree) {
    int flag = 0, order = 0, k = 0, size, number;

    cout << "Enter the number of the tree object, instead of which you want to add a new matrix\n";
    cout << "Now there are " << tree.getNumOfValues() << " objects in the tree ";
    cout << "(0 - " << tree.getNumOfValues() - 1 << ")\n";
    cin >> number;
    cout << "Object number " << number << endl;
    cout << tree[number] << endl;
    cout << "Type the square matrix in the format: at first its dimension (one number), then the matrix itself\n";
    cin >> order;
    auto *mtr = new Matrix(order);
    double array[order * order];
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++, k++) {
            cin >> array[k];
            mtr->setMatrix(i, j, array[k]);
        }
    }
    size = tree.getNumOfValues();
    tree.includeByInd(mtr, number);
    if (size + 1 != tree.getNumOfValues()) flag = 1;
    return flag;
}

int extract(Tree<Matrix> &tree) {
    int flag = 0, size, number;

    cout << "Enter the number of the tree object you want to extract\n";
    cout << "Now there are " << tree.getNumOfValues() << " objects in the tree ";
    cout << "(0 - " << tree.getNumOfValues() - 1 << ")\n";
    cin >> number;

    size = tree.getNumOfValues();
    cout << "Object number " << number << endl;
    cout << tree.extractByInd(number) << endl;

    if (size - 1 != tree.getNumOfValues()) flag = 1;
    return flag;
}

int sort(Tree<Matrix> &tree) {
    int flag = 0, size;

    size = tree.getNumOfValues();
    tree.sortTree();

    if (size != tree.getNumOfValues()) flag = 1;
    else cout << "Sorted\n\n";
    return flag;
}

int includeWithSort(Tree<Matrix> &tree) {
    int flag = 0, order = 0, k = 0, size;
    cout << "Type the square matrix in the format: at first its dimension (one number), then the matrix itself\n";
    cin >> order;
    auto *mtr = new Matrix(order);
    double array[order * order];
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++, k++) {
            cin >> array[k];
            mtr->setMatrix(i, j, array[k]);
        }
    }
    size = tree.getNumOfValues();

    tree.insertWithOrder(mtr);
    if (size + 1 != tree.getNumOfValues()) flag = 1;
    return flag;
}

int saveToBin(Tree<Matrix> &tree) {
    int flag = 0, chs, order, k = 0;
    ofstream fileOut;

    cout << "Choose what you want to do:\n"
            "write the entire tree to a file (1)\nadd new string objects (2)\n";
    cin >> chs;

    if (chs == 1) {
        fileOut.open("../datasets/binText.dat", ios::out | ios::binary);
        if (!fileOut.is_open()) {
            std::cerr << "File open error\n";
            flag = 1;
        } else {
            tree.saveToBin(fileOut);
            fileOut.close();
        }
    }
    if (chs == 2) {
        fileOut.open("../datasets/binText.dat", ios::out | ios::binary | ios::app);
        if (!fileOut.is_open()) {
            std::cerr << "File open error\n";
            flag = 1;
        } else {
            int write = 1, m;
            while (write) {
                cout
                        << "Type the square matrix in the format: at first its dimension (one number), then the matrix itself\n";
                cin >> order;
                auto *mtr = new Matrix(order);
                double array[order * order];
                for (int i = 0; i < order; i++) {
                    for (int j = 0; j < order; j++, k++) {
                        cin >> array[k];
                        mtr->setMatrix(i, j, array[k]);
                    }
                }
                BinaryOut(fileOut, *mtr);
                cout << "Do you want to write more objects in a binary file? (yes [1] / no [2])\n";
                cin >> m;
                if (m == 2) write = 0;
            }
        }
        fileOut.close();
    }
    return flag;
}

int loadFromBin(Tree<Matrix> &tree) {
    int flag = 0;

    ifstream fileIn;
    fileIn.open("../datasets/binText.dat", ios::in | ios::binary);

    if (fileIn.peek() == std::ifstream::traits_type::eof()) {
        cout << "! The file is empty. Save something there first\n\n";
        flag = 1;
    } else {
        if (!fileIn.is_open()) {
            std::cerr << "! File open error\n";
            flag = 1;
        } else {
            tree.loadFromBin(fileIn);
        }
    }
    fileIn.close();
    return flag;
}

void ignoreChars(int &status) {
    if (cin.fail()) status = -1;
    cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}