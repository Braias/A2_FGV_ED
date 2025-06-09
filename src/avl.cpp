#include "tree_utils.h"
#include "avl.h"
#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

namespace AVL {
    BinaryTree* create() {
        BinaryTree* tree = new BinaryTree;
        tree->root = nullptr;
        tree->NIL = nullptr;
        return tree;
    }

    
}
