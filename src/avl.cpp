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
        return balance;
    };

    Node* insert_recursive(Node*& treeRoot, Node* root, const std::string& word, int docId, int& numComparisons){

        // Verifica se a root é vazio
        if(root == nullptr) {
            Node* newNode = new Node{word, {docId}, nullptr, nullptr, nullptr, 1, 0};
            return newNode;
        }

        // Aumenta o número de comparações
        numComparisons++;
        
        if (word < root->word){
            root -> left = insert_recursive(treeRoot, root->left, word, docId, numComparisons);
            if (root -> left) root->left->parent = root;
        }  else if (word > root->word){
            root->right = insert_recursive(treeRoot, root->right, word, docId, numComparisons);
            if (root->right) root->right->parent = root;
            else {
                if (find(root->documentIds.begin(), root->documentIds.end(), docId) == root->documentIds.end()){
                    root->documentIds.push_back(docId);
                }
                return root;
            }

        // Atualiza a altura
        new_height(root);

        // Verifica balanceamento
        int balance = get_balance(root);

        // Rotação
        if (balance < -1 && word < root->left->word) {
            rotate_right(treeRoot, root);
            return root;
        }

        if (balance > 1 && word > root->right->word) {
            rotate_left(treeRoot, root);
            return root;
        }

        if (balance < -1 && word > root->left->word) {
            rotate_left_right(treeRoot, root);
            return root;
        }

        if (balance > 1 && word < root->right->word) {
            rotate_right_left(treeRoot, root);
            return root;
        }

        return root;
        }
    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int docId) {
        InsertResult result;
        // Começa o cronômetro
        auto start = chrono::high_resolution_clock::now();
        
        // Inicializa o número de comparações
        int numComparisons = 0;

        // Insere o nó
        tree->root = insert_recursive(tree->root, tree->root, word, docId, numComparisons); 

        // Para o cronômetro
        auto end = chrono::high_resolution_clock::now();
        result.executionTime = chrono::duration<double, milli>(end - start).count();
        result.numComparisons = numComparisons;
        return result;
    }

}
