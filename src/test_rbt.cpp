#include "tree_utils.h"
#include "rbt.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
using namespace RBT;

/// Função de teste para verificar se a criação de uma árvore binária está correta.
/// Garante que os ponteiros `root` e `NIL` são inicializados corretamente.
void test_create() {
    BinaryTree* tree = create_rbt();
    assert(tree != nullptr);
    assert(tree->NIL != nullptr);

    // Após criação, root deve apontar para NIL
    assert(tree->root == tree->NIL);

    // NIL deve apontar só para nullptrs
    assert(tree->NIL->left == nullptr);
    assert(tree->NIL->right == nullptr);
    assert(tree->NIL->parent == nullptr);

    destroy_rbt(tree);
    cout << "Teste Create passou" << endl;
}


/// Função de teste para inserções na árvore binária de busca.
/// Verifica inserções simples, duplicadas e inserção com string vazia.
void test_insert() {
    BinaryTree* tree = create();

    // Insere "apple" com ID de documento 1
    InsertResult result1 = insert(tree, "apple", 1);
    assert(tree->root != nullptr);
    assert(tree->root->word == "apple");
    assert(tree->root->documentIds.size() == 1);
    assert(tree->root->documentIds[0] == 1);
    assert(result1.numComparisons == 0); // Primeira inserção não faz comparações

    // Insere "banana" (irá para a direita)
    InsertResult result2 = insert(tree, "banana", 1);
    assert(tree->root->right != nullptr);
    assert(tree->root->right->word == "banana");
    assert(result2.numComparisons == 1); // Uma comparação com "apple"

    // Insere novamente "apple" com outro ID de documento
    InsertResult result3 = insert(tree, "apple", 2);
    assert(tree->root->documentIds.size() == 2);
    assert(tree->root->documentIds[1] == 2);  // Segundo ID armazenado

    // Insere string vazia (irá para a esquerda de "apple")
    InsertResult result4 = insert(tree, "", 1);
    assert(tree->root->left != nullptr);
    assert(tree->root->left->word == "");

    destroy_rbt(tree);
    cout << "Teste Insert passou\n";
}

/// Função de teste para busca de palavras na árvore.
/// Verifica se a busca funciona tanto para palavras existentes quanto para inexistentes.
void test_search() {
    BinaryTree* tree = create_rbt();

    insert(tree, "apple", 1);
    insert(tree, "banana", 2);
    insert(tree, "cherry", 3);
    insert(tree, "apple", 4); // Palavra duplicada com outro ID

    SearchResult result1 = search(tree, "apple");
    assert(result1.found == 1);
    assert(result1.documentIds.size() == 2);
    assert(result1.documentIds[0] == 1);
    assert(result1.documentIds[1] == 4);

    SearchResult result2 = search(tree, "zebra");
    assert(result2.found == 0);             // Palavra não encontrada
    assert(result2.documentIds.empty());    // Lista deve estar vazia

    destroy_rbt(tree);
    cout << "Teste Search passou\n";
}

/// Teste para verificar se a destruição da árvore funciona corretamente.
/// Aqui o foco é verificar se a função `destroy` executa sem erros.
void test_destroy() {
    BinaryTree* tree = create_rbt();

    insert(tree, "apple", 1);

    insert(tree, "banana", 2);
    insert(tree, "cherry", 3);

    destroy_rbt(tree);   // Deve liberar memória sem erros
    cout << "Teste Destroy passou\n";
}


/// Teste de busca em árvore vazia.
/// Garante que a função `search` lida corretamente com uma árvore sem nós.
void test_empty_tree_search() {
    BinaryTree* tree = create();

    SearchResult result = search(tree, "anything");
    assert(result.found == 0);              // Nenhum elemento na árvore
    assert(result.documentIds.empty());     // Resultado deve estar vazio

    cout << "Teste EmptyTreeSearch passou\n";
    destroy(tree);
}

void test_rotations_right(){
    BinaryTree* tree = create();
    // Insere nós para fazer árvore ficar desbalanceada à esquerda
    InsertResult result0 = insert(tree, "c", 1);
    InsertResult result2 = insert(tree, "b", 2);
    InsertResult result1 = insert(tree, "a", 3);

    // Ordem final esperada
    assert(tree->root->word == "b");
    assert(tree->root->left->word == "a");
    assert(tree->root->right->word == "c");
    cout << "Teste Rotations Right passou\n";
}

void test_rotations_left(){
    BinaryTree* tree = create();
    // Insere nós para fazer árvore ficar desbalanceada à direita
    InsertResult result1 = insert(tree, "a", 3);
    InsertResult result2 = insert(tree, "b", 2);
    InsertResult result0 = insert(tree, "c", 1);

    // Ordem final esperada
    assert(tree->root->word == "b");
    assert(tree->root->left->word == "a");
    assert(tree->root->right->word == "c");
    cout << "Teste Rotations Left passou\n";
}

void test_rotations_left_right(){
    BinaryTree* tree = create();
    // Insere nós para fazer árvore ficar desbalanceada à esquerda e direita
    InsertResult result0 = insert(tree, "c", 1);
    InsertResult result1 = insert(tree, "a", 3);
    InsertResult result2 = insert(tree, "b", 2);

    // Ordem final esperada
    assert(tree->root->word == "b");
    assert(tree->root->left->word == "a");
    assert(tree->root->right->word == "c");
    cout << "Teste Rotations Left Right passou\n";
}

void test_rotations_right_left(){
    BinaryTree* tree = create();
        // Insere nós para fazer árvore ficar desbalanceada à direita e esquerda
    InsertResult result1 = insert(tree, "a", 3);
    InsertResult result0 = insert(tree, "c", 1);
    InsertResult result2 = insert(tree, "b", 2);

    // Ordem final esperada
    assert(tree->root->word == "b");
    assert(tree->root->left->word == "a");
    assert(tree->root->right->word == "c");
    cout << "Teste Rotations Right Left passou\n";
}

/// Função principal que executa todos os testes da árvore binária de busca (AVL).
int main() {
    cout << "Começando testes RBT\n\n";

    test_create();
    test_insert();
    test_search();
    test_destroy();
    test_empty_tree_search();
    test_rotations_right();
    test_rotations_left();
    test_rotations_left_right();
    test_rotations_right_left();
    cout << "\n Os testes de RBT passaram\n";
    return 0;
}

