#include "tree_utils.h"
#include "bst.h"
#include <iostream>

// TODO: Adicionar insert
// TODO: Adicionar search

namespace BST {

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {

};

SearchResult search(BinaryTree* tree, const std::string& word) {

};


void destroyNode(Node* node) {
    if (node != nullptr) {
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }
}

void destroy(BinaryTree* tree) {
    destroyNode(tree->root);
    delete tree;
};

}