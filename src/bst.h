#ifndef BST_H
#define BST_H
#include "tree_utils.h"

Node* treeSearch(Node* root, std::string word);

Node* createNode(wordStruct wordStruct);

Node* insert(Node* root, wordStruct wordStruct);

#endif 