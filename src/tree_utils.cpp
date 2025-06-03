#include "tree_utils.h"
#include <iostream>

BinaryTree* create() {
    
};


Node* createNode(wordStruct wordStruct) {
    Node* n = new Node();
    n->word = wordStruct.word;
    n->left = nullptr;
    n->right = nullptr;
    n->parent = nullptr;

    return n;
}