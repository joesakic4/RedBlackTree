#include <iostream>
#include "RBT.h"

int main() {
    RBT<int> tree;
    int arr[10] {3, 1, 8, 5, 12, 5, 17, 20, 14, 9};
    for (auto x: arr) {
        tree.insert(x);
        tree.printTree();
        std::cout << std::endl;
    }

}