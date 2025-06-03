#include "tree_utils.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void printTreeRecursive(Node* node, string prefix, bool left) {
    if (node == nullptr) {
        return;
    };

    cout << prefix;

    cout << (left ? "|--" : "L--" );

    cout << node->word << endl;

    printTreeRecursive(node->left, prefix + (left ? "|   " : "    "), true);
    printTreeRecursive(node->right, prefix + (left ? "|   " : "    "), false);
}

void printTree(BinaryTree* tree) {
    printTreeRecursive(tree->root, "", false);
}