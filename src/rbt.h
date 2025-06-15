#ifndef RBT_H
#define RBT_H

#include "tree_utils.h"
#include <string>

namespace RBT {
    bool is_red(Node* node);
    bool is_black(Node* node);

    void set_color(Node* node, int color);

    Node* get_uncle(Node* node);
    Node* get_grandpa(Node* node);

    Node* insert_recursive(Node*& treeRoot, Node* current, const std::string& word, int docId, int& numComparisons);
    void fix_insert(Node*& treeRoot, Node* node);
    InsertResult insert(BinaryTree* tree, const std::string& word, int docId);
}

#endif