#include "tree_utils.h"
#include "rbt.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

namespace RBT {
    BinaryTree* create_rbt() {
        BinaryTree* tree = new BinaryTree;
        tree->NIL = new Node();
        tree->NIL->isRed = 0;  // NIL sempre preto
        tree->NIL->left = tree->NIL->right = tree->NIL->parent = nullptr;
        tree->root = tree->NIL;
        return tree;
    }

    void destroy_node_rbt(Node* node, Node* NIL) {
        if (node != NIL) {
            destroy_node_rbt(node->left, NIL);
            destroy_node_rbt(node->right, NIL);
            delete node;
        }
    }

    void destroy_rbt(BinaryTree* tree) {
        destroy_node_rbt(tree->root, tree->NIL);
        delete tree->NIL;
        delete tree;
    }

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

    void fix_insert(BinaryTree* tree, Node* node) {
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
            fix_insert(tree, grandpa);
            return;
        }

        // tio preto/nulo
        // nó direito pai esquerdo
        if (node == parent->right && parent == grandpa->left) {
            rotate_left_rbt(tree, parent);
            node = parent;
            parent = node->parent;
        }
        // nó esquerdo pai direito
        else if (node == parent->left && parent == grandpa->right) {
            rotate_right_rbt(tree, parent);
            node = parent;
            parent = node->parent;
        }

        // nó esquerdo pai esquerdo
        if (node == parent->left && parent == grandpa->left) {
            set_color(parent, 0);
            set_color(grandpa, 1);
            rotate_right_rbt(tree, grandpa);
        }
        // nó direito pai direito
        else if (node == parent->right && parent == grandpa->right) {
            set_color(parent, 0);
            set_color(grandpa, 1);
            rotate_left_rbt(tree, grandpa);
        }
    }
    Node* insert_recursive(BinaryTree* tree, Node* current, const std::string& word, int docId, int& numComparisons, Node** newlyInserted){

        // Verifica se a current é vazio
        if(current == tree->NIL) {
            Node* newNode = new Node{word, {docId}, nullptr, tree->NIL, tree->NIL, 1, 1};
            *newlyInserted = newNode;
            return newNode;
        }

        // Aumenta o número de comparações
        numComparisons++;

        if (word < current->word){
            current -> left = insert_recursive(tree, current->left, word, docId, numComparisons, newlyInserted);
            if (current -> left) current->left->parent = current;
        }
        else if (word > current->word){
            current -> right = insert_recursive(tree, current->right, word, docId, numComparisons, newlyInserted);
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

        return current;
    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int docId) {
        InsertResult result;
        // Começa o cronômetro
        auto start = chrono::high_resolution_clock::now();

        // Inicializa o número de comparações
        int numComparisons = 0;
        Node* newlyInserted = nullptr;

        // Insere o nó
        tree->root = RBT::insert_recursive(tree, tree->root, word, docId, numComparisons, &newlyInserted);

        if (tree->root != nullptr) {
            set_color(tree->root, 0);
        }

        if (newlyInserted != nullptr) {
            fix_insert(tree, newlyInserted);

        }
        // Para o cronômetro
        auto end = chrono::high_resolution_clock::now();
        result.executionTime = chrono::duration<double, milli>(end - start).count();
        result.numComparisons = numComparisons;
        return result;
    }

    void transplant_rbt(BinaryTree* tree , Node* u, Node* v) {
        if (u->parent == nullptr) {
            tree -> root = v;  // Se u for raíz, v vira raíz da árvore
        } else if (u == u->parent->left) {
            u->parent->left = v; // Faz o pai apontar para v
        } else {
            u->parent->right = v;
        }

        if (v != nullptr) {
            v->parent = u->parent; // Conecta v com o novo pai
        }
    }

    Node* rotate_left_rbt(BinaryTree* tree, Node* root) {
        Node* newRoot = root->right;
        if (newRoot == nullptr) return root;

        root->right = newRoot->left; // Substitui o filho direito por filho esquerdo de newRoot
        if (newRoot->left != nullptr) {
            newRoot->left->parent = root; // Atualiza o pai do filho transferido
        }

        transplant_rbt(tree, root, newRoot);

        newRoot->left = root; // root vira filho esquerdo de newRoot
        root->parent = newRoot; // Atualiza ponteiro de pai

        return newRoot;
    }

    Node* rotate_right_rbt(BinaryTree* tree, Node* root) {
        Node* newRoot = root->left;
        if (newRoot == nullptr) return root;

        root->left = newRoot->right; // Substitui o filho esquerdo por filho direito de newRoot
        if (newRoot->right != nullptr) {
            newRoot->right->parent = root; // Atualiza pai do filho transferido
        }

        // Substitui root por NewRoot
        transplant_rbt(tree, root, newRoot);

        newRoot->right = root; // root vira filho direito de newRoot
        root->parent = newRoot; // Atualiza ponteiro de pai

        return newRoot;
    }

}