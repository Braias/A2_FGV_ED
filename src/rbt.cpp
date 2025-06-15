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

    void fix_insert(Node*& treeRoot, Node* node) {
        Node* parent = node->parent;

        // nó raiz
        if (parent == nullptr) {
            set_color(node, false);
            return;
        }

        // pai preto
        if (!parent->isRed) {
            return;
        }

        // pai vermelho
        Node* grandpa = get_grandpa(node);
        Node* uncle = get_uncle(node);

        // pai e tio vermelhos
        if (uncle->isRed) {
            set_color(parent, false);
            set_color(uncle, false);
            set_color(grandpa, true);
            fix_insert(treeRoot, grandpa);
            return;
        }

        // tio preto/nulo
        // nó direito pai esquerdo
        if (node == parent->right && parent == grandpa->left) {
            rotate_left(treeRoot, parent);
            node = parent;
            parent = node->parent;
        }
        // nó esquerdo pai direito
        else if (node == parent->left && parent == grandpa->right) {
            rotate_right(treeRoot, parent);
            node = parent;
            parent = node->parent;
        }

        // nó esquerdo pai esquerdo
        if (node == parent->left && parent == grandpa->left) {
            set_color(parent, false);
            set_color(grandpa, true);
            rotate_right(treeRoot, grandpa);
        }
        // nó direito pai direito
        else if (node == parent->right && parent == grandpa->right) {
            set_color(parent, false);
            set_color(grandpa, true);
            rotate_left(treeRoot, grandpa);
        }
    }

}