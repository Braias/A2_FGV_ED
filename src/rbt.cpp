#include "tree_utils.h"
#include "rbt.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

namespace RBT {
    void set_color(Node* node, int isRed){
        if (node != nullptr) {
            node->isRed = isRed;
        }
    }

    Node* get_grandpa(Node* node) {
        if (node == nullptr || node->parent == nullptr) {
            return nullptr;
        }
        return node->parent->parent;
    }

    Node* get_uncle(Node* node) {
        Node* grandpa = get_grandpa(node);

        if (grandpa == nullptr){
            return nullptr;
        }

        if (node->parent == grandpa->left) {
            return grandpa->right;
        } else {
            return grandpa->left;
        }
    }

    void fix_insert(Node*& treeRoot, Node* node) {
        Node* parent = node->parent;

        // nó raiz
        if (parent == nullptr) {
            set_color(node, 0);
            return;
        }

        // pai preto
        if (parent->isRed == 0) {
            return;
        }

        // pai vermelho
        Node* grandpa = get_grandpa(node);
        Node* uncle = get_uncle(node);

        // pai e tio vermelhos
        if (uncle != nullptr && uncle->isRed == 1) {
            set_color(parent, 0);
            set_color(uncle, 0);
            set_color(grandpa, 1);
            fix_insert(treeRoot, grandpa);
            return;
        }

        // tio preto/nulo
        // nó direito pai esquerdo
        if (node == parent->right && parent == grandpa->left) {
            rotate_left(treeRoot, parent);
            node = parent;
            parent = node->parent;
        }
        // nó esquerdo pai direito
        else if (node == parent->left && parent == grandpa->right) {
            rotate_right(treeRoot, parent);
            node = parent;
            parent = node->parent;
        }

        // nó esquerdo pai esquerdo
        if (node == parent->left && parent == grandpa->left) {
            set_color(parent, 0);
            set_color(grandpa, 1);
            rotate_right(treeRoot, grandpa);
        }
        // nó direito pai direito
        else if (node == parent->right && parent == grandpa->right) {
            set_color(parent, 0);
            set_color(grandpa, 1);
            rotate_left(treeRoot, grandpa);
        }
    }
    Node* insert_recursive(Node*& treeRoot, Node* current, const std::string& word, int docId, int& numComparisons){

        // Verifica se a current é vazio
        if(current == nullptr) {
            Node* newNode = new Node{word, {docId}, nullptr, nullptr, nullptr, 1, 1};
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
        TREE_UTILS_H::new_height(current);

        if (current->left && current->left->isRed == 1) {
            fix_insert(treeRoot, current->left);
        }
        if (current->right && current->right->isRed == 1) {
            fix_insert(treeRoot, current->right);
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
        tree->root = RBT::insert_recursive(tree->root, tree->root, word, docId, numComparisons);

        if (tree->root != nullptr) {
            set_color(tree->root, 0);
        }

        // Para o cronômetro
        auto end = chrono::high_resolution_clock::now();
        result.executionTime = chrono::duration<double, milli>(end - start).count();
        result.numComparisons = numComparisons;
        return result;
    }
}