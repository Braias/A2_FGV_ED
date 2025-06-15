#include "tree_utils.h"
#include "rbt.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

namespace RBT {
    void set_color(Node* node, bool isRed){
        if (node != nullptr) {
            node->isRed = isRed;
        }
    }

    Node* get_grandpa(Node* node) {
        if (node == nullptr || node->parent == nullptr) {
            return nullptr;
        }
        return node->parent->parent;
    }

    Node* get_uncle(Node* node) {
        Node* grandpa = get_grandpa(node);

        if (grandpa == nullptr){
            return nullptr;
        }

        if (node->parent == grandpa->left) {
            return grandpa->right;
        } else {
            return grandpa->left;
        }
    }
}