#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <string>
#include <vector>

/**
 * @brief Estrutura geral para nó de árvore qualquer,
 * usado para criar índice invertido
 * 
 * Guarda uma palavra única e as ids dos documentos em que essa palavra aparece 
 */
struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
};

/**
 * @brief Estrutura de uma árvore binária, guarda um ponteiro para a raíz da árvore
 * e um ponteiro para NIL (ponteiro para folhas)
 */
struct BinaryTree {
    Node* root;
    Node* NIL;  // usado na apenas na RBT (Opcional)
};

/**
 * @brief Estrutura que guarda informações sobre uma palavra de um documento
 * guarda o nome da palavra e um vetor com os ids dos documentos em que essa palavra aparece
 */
struct wordStruct {
    std::string word;
    std::vector<int> documentIds;
};

/**
 * @brief Estrutura usada para analisar complexidade de operações e tempo nas operações de inserção
 */
struct InsertResult {
    int numComparisons;
    double executionTime;
};

/**
 * @brief Estrutura usada para retornar um processo de busca em uma árvore,
 * guarda um vetor de ids dos documentos em que essa palavra aparece e dados para análise de complexidade,
 * além de dizer se a palavra foi encontrada ou não
 */
struct SearchResult {
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
};

/**
 * @brief Função que printa o index recursivamente, usado por printIndex
 * @param node Nó que será printado
 */
void printIndexRecursive(Node* node);

/**
 * @brief Função que recebe uma árvore e mostra no console as palavras da árvore seguindo a ordem root->esquerda->direita
 * e o id dos documentos em que cada palavra aparece
 * @param tree ponteiro para a raíz da árvore
 */
void printIndex(BinaryTree* tree);

/**
 * @brief Função que printa a estrutura da árvore recursivamente, usado por printTree
 * @param node Nó para ser printado
 * @param prefix Usado para desenhar a estrutura da árvore
 * @param left Indica se o desenho é de um nó a esquerda ou direita
 */
void printTreeRecursive(Node* node, std::string prefix, bool left);

/**
 * @brief Função que recebe uma árvore e mostra no console a estrutura hierárquica da árvore
 * @param tree ponteiro para a raíz da árvore
 */
void printTree(BinaryTree* tree);

#endif