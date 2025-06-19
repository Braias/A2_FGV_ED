#ifndef RBT_H
#define RBT_H

#include "tree_utils.h"
#include <string>


namespace RBT {
    /**
     * @brief Altera a cor de um nó escolhido para a cor selecionada
     * 
     * @param node Nó que terá a cor alterada
     * @param isRed 0 se preto, 1 se  vermelho
     */
    void set_color(Node* node, int isRed);

    /**
     * @brief Cria uma árvore RBT com um nó NIL sentinela
     * 
     * @return Ponteiro para a árvore RBT
     */
    BinaryTree* create_rbt();

    /**
     * @brief Destrói um nó e seus filhos, recursivamente
     */
    void destroy_node_rbt(Node* node, Node* NIL);

    /**
     * @brief Destrói uma árvore RBT por completo
     */
    void destroy_rbt(BinaryTree* tree);

    /**
     * @brief Encontra o pai do pai de um nó, utilizado para balanceamento da RBT
     * 
     * @param node Ponteiro para o nó que deseja descobrir o avô
     * 
     * @return Ponteiro para o nó avô 
     */
    Node* get_grandpa(Node* node);

    /**
     * @brief Encontra o tio de um nó, utilizado no para balanceamento da RBT
     * 
     * @param node Ponteiro para o nó que deseja descobrir o tio
     * 
     * @return Ponteiro para o nó tio
     */
    Node* get_uncle(Node* node);

    /**
     * @brief Insere um nó recursivamente numa árvore RBT
     * 
     * @param tree Ponteiro para BinaryTree da árvore RBT
     * @param current Ponteiro para nó que será analisado
     * @param word Palavra que será inserida na árvore
     * @param docId Id do documento em que essa palavra aparece
     * @param numComparisons Número de comparações feitas para inserção
     * @param newlyInserted Ponteiro de ponteiro que diz se um nó foi inserido ou não, utilizado para lógica de balanceamento
     */
    Node* insert_recursive(BinaryTree* tree, Node* current, const std::string& word, int docId, int& numComparisons, Node** newlyInserted);

    /**
     * @brief Balanceia e recolore nós após a inserção de um novo nó
     * 
     * @param tree Ponteiro para árvore RBT
     * @param node Ponteiro para o nó que será consertado
     */
    void fix_insert(BinaryTree* tree, Node* node);

    /**
     * @brief Insere uma palavra na árvore RBT
     * 
     * @param tree Ponteiro para BinaryTree da árvore
     * @param word Palavra que será inserida
     * @param docId Id do documento em que a palavra inserida está
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int docId);

    /**
     * @brief Substitui o nó u pelo nó v na árvore, ajustando os ponteiros do pai
     * 
     * Se u for a raíz da árvore, a raíz é atualizada para v
     *
     * @param treeRoot Referência para o ponteiro da raíz da árvore
     * @param u Nó a ser substituído
     * @param v Nó que ocupará o lugar de u
     */
    void transplant_rbt(BinaryTree* tree, Node* u, Node* v);

    /**
     * @brief Faz uma rotação à direita numa árvore RBT, atualizando cores dos nós
     * 
     * @param tree Ponteiro para BinaryTree da árvore RBT
     * @param root Ponteiro para raíz da subárvore que será rotacionada
     */
    Node* rotate_right_rbt(BinaryTree* tree, Node* root);

    /**
     * @brief Faz uma rotação à esquerda numa árvore RBT, atualizando cores dos nós
     * 
     * @param tree Ponteiro para BinaryTree da árvore RBT
     * @param root Ponteiro para raíz da subárvore que será rotacionada
     */
    Node* rotate_left_rbt(BinaryTree* tree, Node* root);
}
#endif
