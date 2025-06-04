#include "tree_utils.h"
#include <iostream>
#include <algorithm>
#include <string>

// TODO: Adicionar printIndex (mesma ideia de printTree)

using namespace std;

void printIndexRecursive(Node* node) {
    if (node == nullptr){
	    return;
    };
    
    printIndexRecursive(node->left);
    cout << node->word << ": ";
    for (size_t i = 0; i < node->documentIds.size(); ++i) {
        cout << node->documentIds[i];
        if (i < node->documentIds.size() - 1)
            cout << ", ";
    }
    cout << endl;
    printIndexRecursive(node->right);
}

void printIndex(BinaryTree* tree) {
    printIndexRecursive(tree->root);
}


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