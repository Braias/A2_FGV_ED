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
 * @brief Cria e inicializa uma nova árvore binária de busca.
 *
 * @return Ponteiro para a estrutura BinaryTree recém-criada.
 */
BinaryTree* create();

// TODO: implementar funções de rotação
/**
 * @brief Faz o pai do primeiro nó apontar para o segundo nó
 */
void transplant(Node* u, Node* v);

Node* rotate_left(Node* node);

Node* rotate_right(Node* node);

Node* rotate_left_right(Node* node);

Node* rotate_right_left(Node* node);

/**
 * @brief Realiza uma busca por uma palavra na árvore binária de busca.
 *
 * @param tree Ponteiro para a árvore onde será feita a busca.
 * @param word Palavra a ser procurada.
 * @return Estrutura SearchResult indicando se a palavra foi encontrada e os IDs associados.
 */
SearchResult search(BinaryTree* tree, const std::string& word);

/**
 * @brief Libera a memória alocada para um nó específico
 * 
 * Após a chamada desta função, o ponteiro do nó não deve mais ser utilizado.
 *
 * @param node Ponteiro para o nó a ser destruído.
 */
void destroyNode(Node* node);

/**
 * @brief Libera toda a memória alocada pela árvore binária de busca.
 *
 * Após a chamada desta função, o ponteiro da árvore não deve mais ser utilizado.
 *
 * @param tree Ponteiro para a árvore a ser destruída.
 */
void destroy(BinaryTree* tree);

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