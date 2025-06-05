#include "tree_utils.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

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