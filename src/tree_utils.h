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
 * @brief Estrutura usada para retornar estatisticas de insercoes em uma arvore
 * guarda a arvore e os valores totais e medios do tempo de insercoes por documento
 * e numero de comparacoes por documento
 */
struct ConstructResult {
    BinaryTree* tree;
    double totalInsertionTime;
    double insertionTimeAVG;
    int totalComparisons;
    double comparisonsAVG;
    std::vector<std::string> unique_words;
};

/**
 * @brief Cria e inicializa uma nova árvore binária de busca
 *
 * @return Ponteiro para a estrutura BinaryTree recém-criada
 */
BinaryTree* create();

/**
 * @brief Substitui o nó u pelo nó v na árvore, ajustando os ponteiros do pai
 * 
 * Se u for a raíz da árvore, a raíz é atualizada para v
 *
 * @param treeRoot Referência para o ponteiro da raíz da árvore
 * @param u Nó a ser substituído
 * @param v Nó que ocupará o lugar de u
 */
void transplant(Node*& treeRoot, Node* u, Node* v);

/**
 * @brief Realiza uma rotação simples à esquerda na subárvore com raíz root
 * 
 * @param treeRoot Referência para a raíz da árvore
 * @param root Ponteiro para o nó onde a rotação será aplicada
 */
void rotate_left(Node*& treeRoot, Node* root);

/**
 * @brief Realiza uma rotação simples à direita na subárvore com raíz root
 * 
 * @param treeRoot Referência para a raíz da árvore
 * @param root Ponteiro para o nó onde a rotação será aplicada
 */
void rotate_right(Node*& treeRoot, Node* root);

/**
 * @brief Realiza uma rotação dupla esquerda-direita
 * 
 * Primeiro aplica uma rotação à esquerda no filho esquerdo de root,
 * depois aplica uma rotação à direita no próprio root
 * 
 * @param treeRoot Referência para a raíz da árvore
 * @param root Ponteiro para o nó onde a rotação será aplicada
 */
void rotate_left_right(Node*& treeRoot, Node* root);

/**
 * @brief Realiza uma rotação dupla direita-esquerda
 * 
 * Primeiro aplica uma rotação à direita no filho direito de root,
 * depois aplica uma rotação à esquerda no próprio root
 * 
 * @param treeRoot Referência para a raíz da árvore
 * @param root Ponteiro para o nó onde a rotação será aplicada
 */
void rotate_right_left(Node*& treeRoot, Node* root);

/**
 * @brief Realiza uma busca por uma palavra na árvore binária de busca
 *
 * @param tree Ponteiro para a árvore onde será feita a busca
 * @param word Palavra a ser procurada
 * @return Estrutura SearchResult indicando se a palavra foi encontrada e os IDs associados
 */
SearchResult search(BinaryTree* tree, const std::string& word);

/**
 * @brief Libera a memória alocada para um nó específico
 * 
 * Após a chamada desta função, o ponteiro do nó não deve mais ser utilizado
 *
 * @param node Ponteiro para o nó a ser destruído
 */
void destroyNode(Node* node);

/**
 * @brief Libera toda a memória alocada pela árvore binária de busca
 *
 * Após a chamada desta função, o ponteiro da árvore não deve mais ser utilizado
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

/**
 * @brief Calcula a altura da árvore.
 * @param tree Arvore a ser medida.
 * @return A altura da árvore. Retorna -1 para uma árvore vazia.
 */
int get_tree_height(const BinaryTree* tree);

/**
 * @brief Encontra o comprimento do caminho mais curto da raiz até um nó folha.
 * @param tree A árvore a ser medida.
 * @return O comprimento do caminho mais curto. Retorna -1 para uma árvore vazia.
 */
int get_shortest_path(const BinaryTree* tree);

#endif