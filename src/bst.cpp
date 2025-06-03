#include "tree_utils.h"
#include <iostream>

// TODO: Fazer checagem para palavras unicas (evitar duplicatas no documentIds)

// Estrutura de wordStruct para testes
struct wordStruct {
    std::string word;
    std::vector<int> documentIds;
};

Node* treeSearch(Node* root, std::string word) {
    if (root == nullptr || root->word == word) {
        return root;
    }

    if (word < root->word) {
        return treeSearch(root->left, word);
    } else {
        return treeSearch(root->right, word);
    }
};

Node* createNode(wordStruct wordStruct) {
    Node* n = new Node();
    n->word = wordStruct.word;
    n->left = nullptr;
    n->right = nullptr;
    n->parent = nullptr;

    return n;
}

Node* insert(Node* root, wordStruct wordStruct) {
    if (root == nullptr) {
        Node* newNode = createNode(wordStruct);
        newNode->documentIds = wordStruct.documentIds;
        return newNode;
    };


    if (wordStruct.word < root->word) {
        Node* leftChild = insert(root->left, wordStruct);
        root->left = leftChild;
        leftChild->parent = root;
    } else if (wordStruct.word > root->word) {
        Node* rightChild = insert(root->right, wordStruct);
        root->right = rightChild;
        rightChild->parent = root;
    } else {
        root->documentIds.insert(root->documentIds.end(), wordStruct.documentIds.begin(), wordStruct.documentIds.end());
        root->word = wordStruct.word;
    };
    return root;
};
