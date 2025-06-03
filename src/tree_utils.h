#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <string>
#include <vector>

struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
};

struct BinaryTree {
    Node* root;
    Node* NIL;  // usado na RBT (Opcional)
};

struct wordStruct {
    std::string word;
    std::vector<int> documentIds;
};

struct InsertResult {
    int numComparisons;
    double executionTime;
};

struct SearchResult {
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
};

void printIndex(BinaryTree* tree);
void printTree(BinaryTree* tree);

#endif