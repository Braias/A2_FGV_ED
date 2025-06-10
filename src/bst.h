#ifndef BST_H
#define BST_H
#include "tree_utils.h"

/// Namespace que inclui as funções da árvore binária de busca
namespace BST {
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
}
#endif