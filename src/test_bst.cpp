#include "tree_utils.h"
#include "bst.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
using namespace BST;

void testCreate() {
    BinaryTree* tree = create();
    assert(tree != nullptr);
    assert(tree->root == nullptr);
    assert(tree->NIL == nullptr);
    cout << "Teste Create passou\n";
    destroy(tree);
}

void testInsert() {
    BinaryTree* tree = create();
    
    InsertResult result1 = insert(tree, "apple", 1);
    assert(tree->root != nullptr);
    assert(tree->root->word == "apple");
    assert(tree->root->documentIds.size() == 1);
    assert(tree->root->documentIds[0] == 1);
    assert(result1.numComparisons == 0);
    
    InsertResult result2 = insert(tree, "banana", 1);
    assert(tree->root->right != nullptr);
    assert(tree->root->right->word == "banana");
    assert(result2.numComparisons == 1);
    
    InsertResult result3 = insert(tree, "apple", 2);
    assert(tree->root->documentIds.size() == 2);
    assert(tree->root->documentIds[1] == 2);
    
    InsertResult result4 = insert(tree, "", 1);
    assert(tree->root->left != nullptr);
    assert(tree->root->left->word == "");
    
    cout << "Teste Insert passou\n";
    destroy(tree);
}

void testSearch() {
    BinaryTree* tree = create();
    
    insert(tree, "apple", 1);
    insert(tree, "banana", 2);
    insert(tree, "cherry", 3);
    insert(tree, "apple", 4);
    
    SearchResult result1 = search(tree, "apple");
    assert(result1.found == 1);
    assert(result1.documentIds.size() == 2);
    assert(result1.documentIds[0] == 1);
    assert(result1.documentIds[1] == 4);
    
    SearchResult result2 = search(tree, "zebra");
    assert(result2.found == 0);
    assert(result2.documentIds.empty());
    
    cout << "Teste Search passou\n";
    destroy(tree);
}

void testDestroy() {
    BinaryTree* tree = create();
    
    insert(tree, "apple", 1);
    insert(tree, "banana", 2);
    insert(tree, "cherry", 3);
    
    destroy(tree);
    cout << "Teste Destroy passou\n";
}


void testEmptyTreeSearch() {
    BinaryTree* tree = create();
    
    SearchResult result = search(tree, "anything");
    assert(result.found == 0);
    assert(result.documentIds.empty());
    
    cout << "Teste EmptyTreeSearch passou\n";
    destroy(tree);
}

int main() {
    cout << "Começando testes BST\n\n";
    
    testCreate();
    testInsert();
    testSearch();
    testDestroy();
    testPerformance();
    testEmptyTreeSearch();
    
    cout << "\n Os testes de BST passaram\n";
    return 0;
}
