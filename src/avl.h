#ifndef AVL_H
#define AVL_H
#include "tree_utils.h"

namespace AVL {

    /**
     * @brief Cria e inicializa uma nova árvore AVL.
     *
     * @return Ponteiro para a estrutura BinaryTree recém-criada.
     */
    BinaryTree* create();

    /**
     * @brief Insere uma palavra na árvore AVL associada a um ID de documento.
     *
     * Se a palavra já existir, apenas adiciona o novo ID à lista correspondente.
     * Realiza as rotações necessárias para manter o balanceamento da árvore.
     *
     * @param tree Ponteiro para a árvore onde a inserção será feita.
     * @param word Palavra a ser inserida.
     * @param documentId ID do documento relacionado à palavra.
     * @return Estrutura InsertResult contendo estatísticas (ex: número de comparações).
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * @brief Realiza uma busca por uma palavra na árvore AVL.
     *
     * @param tree Ponteiro para a árvore onde será feita a busca.
     * @param word Palavra a ser procurada.
     * @return Estrutura SearchResult indicando se a palavra foi encontrada e os IDs associados.
     */
    SearchResult search(BinaryTree* tree, const std::string& word);

    /**
     * @brief Libera toda a memória alocada pela árvore AVL.
     *
     * Após a chamada desta função, o ponteiro da árvore não deve mais ser utilizado.
     *
     * @param tree Ponteiro para a árvore a ser destruída.
     */
    void destroy(BinaryTree* tree);

    int get_height(Node* node);

    int get_balance(Node* node);

    Node* rotate_right(BinaryTree* tree, Node* node);

    Node* rotate_left(BinaryTree* tree, Node* node);

    Node* rotate_left_right(BinaryTree* tree, Node* node);

    Node* rotate_right_left(BinaryTree* tree, Node* node);

    void new_height(Node* node);
}

#endif
