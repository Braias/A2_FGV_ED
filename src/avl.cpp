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

    SearchResult search(BinaryTree* tree, const std::string& word) {
        SearchResult result = {0, {}, 0.0, 0};
        
        // Verifica a existência da árvore
        if (tree->root == nullptr) {
            return result;
        };

        // Começa o cronômetro
        auto start = system_clock::now();

        Node* current = tree->root;
        // Loop de comparação
        do {
            result.numComparisons ++;
            if (current->word == word) {
                result.found = 1;
                result.documentIds = current->documentIds;
                break;
            } else if (current->word < word) {
                current = current->right;
            } else {
                current = current->left;
            }
        }while (current != nullptr);

        // Para o relógio
        auto stop = system_clock::now();
        result.executionTime = duration<double>(stop - start).count();
        return result;    
    };

}
