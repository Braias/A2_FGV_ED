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

int get_height(Node* node){
    if(node == nullptr){
        return 0;
    };
    return node->height;
};

void new_height(Node* node){
    if (node == nullptr) return;
    // Depois da rotação, atualiza a altura
    node->height = 1 + max(get_height(node->left), get_height(node->right));
};

void transplant(Node*& treeRoot, Node* u, Node* v) {
    if (u->parent == nullptr) {
        treeRoot = v;  // u is the actual root
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != nullptr) {
        v->parent = u->parent;
    }
}

void rotate_left(Node*& treeRoot, Node* root) {
    Node* newRoot = root->right;
    if (newRoot == nullptr) return;

    root->right = newRoot->left;
    if (newRoot->left != nullptr) {
        newRoot->left->parent = root;
    }

    transplant(treeRoot, root, newRoot);

    newRoot->left = root;
    root->parent = newRoot;

    new_height(root);
    new_height(newRoot);
}

void rotate_right(Node*& treeRoot, Node* root) {
    Node* newRoot = root->left;
    if (newRoot == nullptr) return;

    root->left = newRoot->right;
    if (newRoot->right != nullptr) {
        newRoot->right->parent = root;
    }

    transplant(treeRoot, root, newRoot);

    newRoot->right = root;
    root->parent = newRoot;

    new_height(root);
    new_height(newRoot);
}

void rotate_left_right(Node*& treeRoot, Node* root) {
    rotate_left(treeRoot, root->left);
    rotate_right(treeRoot, root);
}

void rotate_right_left(Node*& treeRoot, Node* root) {
    rotate_right(treeRoot, root->right);
    rotate_left(treeRoot, root);
}