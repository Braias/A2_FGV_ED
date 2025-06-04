#include "tree_utils.h"
#include "bst.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

namespace BST {

// Função que cria a árvore binária de busca
BinaryTree* create() {
    BinaryTree* tree = new BinaryTree;
    tree->root = nullptr;
    tree->NIL = nullptr;
    return tree;
}

// Função de busca do de um determinado nó
// Verifica se existe um nó com uma determinada palavra e devolve o tempo decorrido, o número de comparações e em quais documentos ela se encontra
SearchResult search(BinaryTree* tree, const std::string& word) {
    // Verifica a existência da árvore
    if (tree->root == nullptr) {
        return;
    };
    // Começa o cronômetro
    SearchResult result = {0, {}, 0.0, 0};
    auto start = system_clock::now();

    Node* current = tree->root;
    // Loop de comparação
    while (current->word != word) {
        result.numComparisons ++;
        if (current->word == word) {
            result.found = 1;
            result.documentIds = current->documentIds;
        } else if (current->word < word) {
            current = current->right;
        } else {
            current = current->left;
        }
    };

    // Parando o cronômetro
    auto stop = system_clock::now();
    result.executionTime = duration<double>(stop - start).count();
    return result;    
};

// Função para deletar um determinado nó da árvore
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

// Função de inserção na árvore binária de busca
// Insere um novo nó (palavra) na árvore
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    InsertResult result;
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
        int currentHeight = 1;

        // Encontrar posição de inserção
        while (current != nullptr) {
            parent = current;
            result.numComparisons++;

            if (word == current->word) {
                // Palavra já existe: apenas adiciona o documento
                current->documentIds.push_back(documentId);
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

    auto end = high_resolution_clock::now();
    result.executionTime = duration<double>(end - start).count();
    return result;
}
}