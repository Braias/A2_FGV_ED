#include "tree_utils.h"
#include "bst.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

namespace BST {
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
        InsertResult result;
        // Inicializa o número de comparações e começa o cronômetro
        result.numComparisons = 0;
        auto start = high_resolution_clock::now();

        // Criar novo nó
        Node* newNode = new Node;
        newNode->word = word;
        newNode->documentIds.push_back(documentId);
        newNode->left = nullptr;  
        newNode->right = nullptr;
        newNode->parent = nullptr;
        newNode->height = 1;

        if (tree->root == nullptr) {  // Árvore vazia
            tree->root = newNode;
        } else {
            Node* current = tree->root;
            Node* parent = nullptr;

            // Encontrar posição de inserção
            while (current != nullptr) {
                parent = current;
                result.numComparisons++;

                if (word == current->word) {
                    // Palavra já existe: apenas adiciona o documento
                    bool found = false;
                    for (const auto& id : current->documentIds) {
                        if (id == documentId) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        current->documentIds.push_back(documentId);
                    }
                    delete newNode;  // Libera o nó não utilizado
                    auto end = high_resolution_clock::now();
                    result.executionTime = duration<double>(end - start).count();
                    return result;
                } else if (word < current->word) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            // Insere o novo nó
            newNode->parent = parent;
            if (word < parent->word) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }

        // Atualiza alturas de baixo pra cima
        Node* node = newNode;
        while (node != nullptr) {
            int leftHeight = node->left ? node->left->height : 0;
            int rightHeight = node->right ? node->right->height : 0;
            if (leftHeight > rightHeight) {
                node->height = 1 + leftHeight;
            } 
            else {
                node->height = 1 + rightHeight;
            }
            node = node->parent;
        }

        // Para o cronômetro
        auto end = high_resolution_clock::now();
        result.executionTime = duration<double>(end - start).count();
        return result;
    }
}