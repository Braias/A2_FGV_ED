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
    SearchResult result = {0, {}, 0.0, 0,-1};
    
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
            result.nodeHeight = current->height;
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
    
void destroy_node(Node* node) {
    // Caso o nó não seja nulo, o nó e seus filhos são destruídos
    if (node != nullptr) {
        destroy_node(node->left);
        destroy_node(node->right);
        delete node;
    }
}

void destroy(BinaryTree* tree) {
    destroy_node(tree->root);
    delete tree;
};

void print_index_recursive(Node* node) {
    if (node == nullptr){
        // Caso base: se o nó for nulo, encerra a recursão
	    return;
    };

    // Percorre primeiro a subárvore da esquerda (ordem simétrica)
    print_index_recursive(node->left);

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
    print_index_recursive(node->right);
}

void print_index(BinaryTree* tree) {
    print_index_recursive(tree->root);
}


void print_tree_recursive(Node* node, string prefix, bool left) {
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
    print_tree_recursive(node->left, prefix + (left ? "|   " : "    "), true);
    // Recorre o filho a direita
    print_tree_recursive(node->right, prefix + (left ? "|   " : "    "), false);
}

void print_tree(BinaryTree* tree) {
    print_tree_recursive(tree->root, "", false);
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
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    int max_height = (left_height > right_height) ? left_height : right_height; 
    node-> height = 1 + max_height;
};

void transplant(Node*& treeRoot, Node* u, Node* v) {
    if (u->parent == nullptr) {
        treeRoot = v;  // Se u for raíz, v vira raíz da árvore
    } else if (u == u->parent->left) {
        u->parent->left = v; // Faz o pai apontar para v
    } else {
        u->parent->right = v;
    }

    if (v != nullptr) {
        v->parent = u->parent; // Conecta v com o novo pai
    }
}

Node* rotate_left(Node*& treeRoot, Node* root) {
    Node* newRoot = root->right;
    if (newRoot == nullptr) return root;

    root->right = newRoot->left; // Substitui o filho direito por filho esquerdo de newRoot
    if (newRoot->left != nullptr) {
        newRoot->left->parent = root; // Atualiza o pai do filho transferido
    }

    // Substitui root por NewRoot
    transplant(treeRoot, root, newRoot);

    newRoot->left = root; // root vira filho esquerdo de newRoot
    root->parent = newRoot; // Atualiza ponteiro de pai

    // Recomputa alturas
    new_height(root);
    new_height(newRoot);
    return newRoot;
}

Node* rotate_right(Node*& treeRoot, Node* root) {
    Node* newRoot = root->left;
    if (newRoot == nullptr) return root;

    root->left = newRoot->right; // Substitui o filho esquerdo por filho direito de newRoot
    if (newRoot->right != nullptr) {
        newRoot->right->parent = root; // Atualiza pai do filho transferido
    }

    // Substitui root por NewRoot
    transplant(treeRoot, root, newRoot);

    newRoot->right = root; // root vira filho direito de newRoot
    root->parent = newRoot; // Atualiza ponteiro de pai

    // Recomputa alturas
    new_height(root);
    new_height(newRoot);
    return newRoot;
}

Node* rotate_left_right(Node*& treeRoot, Node* root) {
    root->left = rotate_left(treeRoot, root->left); // Primeiro, rotação à esquerda no filho esquerdo
    return rotate_right(treeRoot, root); // Depois, rotação à direita no próprio root
}

Node* rotate_right_left(Node*& treeRoot, Node* root) {
    root->right = rotate_right(treeRoot, root->right); // Primeiro, rotação à direita no filho direito
    return rotate_left(treeRoot, root); // Depois, rotação à esquerda no próprio root
}

int get_tree_height(const BinaryTree* tree) {
    if (tree == nullptr || tree->root == nullptr) {
        return -1; // Árvore vazia
    }
    return tree->root->height - 1;
}

int find_min_depth(const Node* node) {
    if (node == nullptr) {
        return -1;
    }

    if (node->left == nullptr && node->right == nullptr) {
        return 0;
    }

    if (node->left == nullptr) {
        return 1 + find_min_depth(node->right); // Só há caminho à direita
    }
    if (node->right == nullptr) {
        return 1 + find_min_depth(node->left); // Só há caminho à esquerda
    }

    // Tem ambos os filhos — retorna o menor caminho
    int left_depth = find_min_depth(node->left);
    int right_depth = find_min_depth(node->right);

    int min_child_depth = (left_depth < right_depth) ? left_depth : right_depth;
    return 1 + min_child_depth;
}

int get_shortest_path(const BinaryTree* tree) {
    if (tree == nullptr || tree->root == nullptr) {
        return -1;
    }
    return find_min_depth(tree->root);
}