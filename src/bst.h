#ifndef BST_H
#define BST_H
#include "tree_utils.h"

/// Namespace que inclui as funções da árvore binária de busca
namespace BST {

    /**
     * @brief Cria e inicializa uma nova árvore binária de busca.
     *
     * @return Ponteiro para a estrutura BinaryTree recém-criada.
     */
    BinaryTree* create();

    /**
     * @brief Insere uma palavra na árvore binária de busca associada a um ID de documento.
     *
     * Se a palavra já existir, apenas adiciona o novo ID à lista correspondente.
     *
     * @param tree Ponteiro para a árvore onde a inserção será feita.
     * @param word Palavra a ser inserida.
     * @param documentId ID do documento relacionado à palavra.
     * @return Estrutura InsertResult contendo estatísticas (ex: número de comparações).
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * @brief Realiza uma busca por uma palavra na árvore binária de busca.
     *
     * @param tree Ponteiro para a árvore onde será feita a busca.
     * @param word Palavra a ser procurada.
     * @return Estrutura SearchResult indicando se a palavra foi encontrada e os IDs associados.
     */
    SearchResult search(BinaryTree* tree, const std::string& word);

    /**
     * @brief Libera toda a memória alocada pela árvore binária de busca.
     *
     * Após a chamada desta função, o ponteiro da árvore não deve mais ser utilizado.
     *
     * @param tree Ponteiro para a árvore a ser destruída.
     */
    void destroy(BinaryTree* tree);
}

#endif