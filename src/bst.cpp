#include "tree_utils.h"
#include "bst.h"
#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

namespace BST {
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

    void destroyNode(Node* node) {
        // Caso o nó não seja nulo, o nó e seus filhos são destruídos
        if (node != nullptr) {
            destroyNode(node->left);
            destroyNode(node->right);
            delete node;
        }
    }

    void destroy(BinaryTree* tree) {
        destroyNode(tree->root);
        delete tree;
    };

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
                    if(find(current->documentIds.begin(), current->documentIds.end(), documentId) == current->documentIds.end()){
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

        // Para o cronômetro
        auto end = high_resolution_clock::now();
        result.executionTime = duration<double>(end - start).count();
        return result;
    }
}