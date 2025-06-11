#include "tree_utils.h"
#include "avl.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

namespace AVL {
    int get_balance(Node* node){
        if (node == nullptr) return 0;
        else {
            int balance = TREE_UTILS_H::get_height(node->right) - TREE_UTILS_H::get_height(node->left);
            return balance;
        }
    };

    Node* insert_recursive(Node*& treeRoot, Node* current, const std::string& word, int docId, int& numComparisons){

        // Verifica se a current é vazio
        if(current == nullptr) {
            Node* newNode = new Node{word, {docId}, nullptr, nullptr, nullptr, 1, 0};
            return newNode;
        }

        // Aumenta o número de comparações
        numComparisons++;
        
        if (word < current->word){
            current -> left = insert_recursive(treeRoot, current->left, word, docId, numComparisons);
            if (current -> left) current->left->parent = current;
        }  
        else if (word > current->word){
            current->right = insert_recursive(treeRoot, current->right, word, docId, numComparisons);
            if (current->right) current->right->parent = current;}
        else {
            bool exists = false;
            for (int id : current->documentIds) {
                if (id == docId) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                current->documentIds.push_back(docId);
            }
            return current;
        }


        // Atualiza a altura
        TREE_UTILS_H::new_height(current);

        // Verifica balanceamento
        int balance = get_balance(current);

        // Rotação
        if (balance < -1 && word < current->left->word) {
            return rotate_right(treeRoot, current);
        }

        if (balance > 1 && word > current->right->word) {
            return rotate_left(treeRoot, current);
        }

        if (balance < -1 && word > current->left->word) {
            return rotate_left_right(treeRoot, current);
        }

        if (balance > 1 && word < current->right->word) {
            return rotate_right_left(treeRoot, current);
        }
        return current;
    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int docId) {
        InsertResult result;
        // Começa o cronômetro
        auto start = chrono::high_resolution_clock::now();
        
        // Inicializa o número de comparações
        int numComparisons = 0;

        // Insere o nó
        tree->root = AVL::insert_recursive(tree->root, tree->root, word, docId, numComparisons);

        // Para o cronômetro
        auto end = chrono::high_resolution_clock::now();
        result.executionTime = chrono::duration<double, milli>(end - start).count();
        result.numComparisons = numComparisons;
        return result;
    }

}
