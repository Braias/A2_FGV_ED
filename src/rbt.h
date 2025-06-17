#ifndef RBT_H
#define RBT_H

#include "tree_utils.h"
#include <string>


namespace RBT {
    void set_color(Node* node, int isRed);

    BinaryTree* create_rbt();
    void destroy_node_rbt(Node* node, Node* NIL);
    void destroy_rbt(BinaryTree* tree);

    Node* get_grandpa(Node* node);
    Node* get_uncle(Node* node);

    Node* insert_recursive(Node*& treeRoot, Node* current, const std::string& word, int docId, int& numComparisons);
    void fix_insert(Node*& treeRoot, Node* node);

    InsertResult insert(BinaryTree* tree, const std::string& word, int docId);
}
#endif
