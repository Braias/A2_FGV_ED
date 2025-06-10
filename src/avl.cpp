#include "tree_utils.h"
#include "avl.h"
#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

namespace AVL {
    int get_height(Node* node){
        if(node == nullptr){
            return 0;
        };
        return node->height;
    };

    void new_height(Node* node){
        // Depois da rotação, atualiza a altura
        node->height = 1 + max(get_height(node->left), get_height(node->right));
    };

    int get_balance(Node* node){
        int balance = node->right->height - node->left->height;
    };
}
