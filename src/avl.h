#ifndef AVL_H
#define AVL_H
#include "tree_utils.h"

namespace AVL {
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
     * @brief Calcula o balanceamento da subárvore com raiz node
     * Se balance é maior que 1, a árvore está desbalanceada para a direita
     * Se balance é menor que 1, a árvore está desbalanceada para a esquerda
     * 
     * @param node Ponteiro para o nó a ser analisado
     * 
     * @return Número de balanceamento 
     */
    int get_balance(Node* node);
}

#endif
