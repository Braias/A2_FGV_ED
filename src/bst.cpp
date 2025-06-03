#include "tree_utils.h"
#include "bst.h"
#include <iostream>
#include <chrono>

// TODO: Adicionar insert

using namespace std;
using namespace chrono;

namespace BST {

BinaryTree* create() {
    BinaryTree* tree = new BinaryTree;
    tree->root = nullptr;
    tree->NIL = nullptr;
    return tree;
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {

};

SearchResult search(BinaryTree* tree, const std::string& word) {
    if (tree->root == nullptr) {
        return;
    };

    SearchResult result = {0, {}, 0.0, 0};
    auto start = system_clock::now();

    Node* current = tree->root;
    while (current->word != word) {
        result.numComparisons ++;
        if (current->word == word) {
            result.found = 1;
            result.documentIds = current->documentIds;
        } else if (current->word < word) {
            current = current->right;
        } else {
            current = current->left;
        }
    };

    auto stop = system_clock::now();
    result.executionTime = duration<double>(stop - start).count();
    return result;    
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