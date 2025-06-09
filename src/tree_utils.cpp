#include "tree_utils.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

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

void printIndexRecursive(Node* node) {
    if (node == nullptr){
        // Caso base: se o nó for nulo, encerra a recursão
	    return;
    };

    // Percorre primeiro a subárvore da esquerda (ordem simétrica)
    printIndexRecursive(node->left);

    // Imprime a palavra armazenada no nó
    cout << node->word << ": ";
    for (size_t i = 0; i < node->documentIds.size(); ++i) {
        // printa os ids dos documentos entre vírgulas
        cout << node->documentIds[i];
        if (i < node->documentIds.size() - 1)
            cout << ", ";
    }
    cout << endl;

    // Percorre a subárvore da direita
    printIndexRecursive(node->right);
}

void printIndex(BinaryTree* tree) {
    printIndexRecursive(tree->root);
}


void printTreeRecursive(Node* node, string prefix, bool left) {
    if (node == nullptr) {
        return;
    };

    // Imprime o prefixo para manter o alinhamento visual
    cout << prefix;

    // Determina o tipo de ramificação: esquerda ou direita
    cout << (left ? "|--" : "L--" );

    // Imprime a palavra armazenada no nó
    cout << node->word << endl;

    // Recorre o filho a esquerda
    printTreeRecursive(node->left, prefix + (left ? "|   " : "    "), true);
    // Recorre o filho a direita
    printTreeRecursive(node->right, prefix + (left ? "|   " : "    "), false);
}

void printTree(BinaryTree* tree) {
    printTreeRecursive(tree->root, "", false);
}