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

    Node* insert_recursive(BinaryTree* tree, Node* current, const std::string& word, int docId, int& numComparisons);
    void fix_insert(BinaryTree* tree, Node* node);

    InsertResult insert(BinaryTree* tree, const std::string& word, int docId);

    void transplant_rbt(BinaryTree* tree, Node* u, Node* v);
    Node* rotate_right_rbt(BinaryTree* tree, Node* root);
    Node* rotate_left_rbt(BinaryTree* tree, Node* root);
    Node* rotate_right_left_rbt(BinaryTree* tree, Node* root);
    Node* rotate_left_right_rbt(BinaryTree* tree, Node* root);
}
#endif
