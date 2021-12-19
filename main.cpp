#include <iostream>
#include <fstream>
#include "Tree.h"
//#include "TreeNode.h"

int main() {
    Tree<Matrix> tr;
    Matrix arr[10];

    ifstream fileOut;
    fileOut.open("../text.txt");
    if (!fileOut.is_open()) {
        std::cerr << "File open error" << "\n";
        exit(1);
    }
    for (auto &i: arr) {
        fileOut >> i;
    }
    fileOut.close();

    for (auto &i: arr) {
        tr.insertValue(&i);
    }

    Matrix a(2);
    int arr_a[4] = {3, 7, 12, 9};
    int k = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++, k++)
            a.SetMatrix(i, j, arr_a[k]);

//   tr[0] = a;
//    tr.printTree();
//    TreeNode node = tr[1];
//    cout << endl << tr[3];
    cout << "*****************************" << endl;
//    cout << tr.extractByInd(3);
    tr.sortTree();
    tr.printTree();
//    cout << tr[0].summary() << endl;
//    cout << tr[1].summary() << endl;
//    cout << endl << tr[3];

//    tr.printStats();

    /* ofstream binFileIn;
     binFileIn.open("../binText.dat", ios::binary);
     if (!binFileIn.is_open()) {
         std::cerr << "File open error" << "\n";
         exit(1);
     }
 //    BinaryIn(binFileIn, a);
     tr.saveToBin(binFileIn);
     binFileIn.close();

     ifstream binFileOut;
     binFileOut.open("../binText.dat", ios::binary);
     if (!binFileOut.is_open()) {
         std::cerr << "File open error" << "\n";
         exit(1);
     }
     tr.loadFromBin(binFileOut);
     binFileOut.close();*/
//    Tree<int> tr2;
//    int array[10] = {5, 2, 8, 9, 1, 10, 3, 7, 4, 6};
//    for (int i = 0; i < 10; ++i) {
//        tr2.insertValue(&array[i]);
//    }
//    int t = 3;
////    tr2.insertValue(&t);
//    tr2.sortTree();
//    tr2.insertWithOrder(&t);
//    tr2.printTree();
    return 0;
}
