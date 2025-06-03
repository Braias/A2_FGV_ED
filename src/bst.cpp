#include "tree_utils.h"
#include <iostream>

// TODO: Fazer checagem para palavras unicas (evitar duplicatas no documentIds)


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

#include "tree_utils.h"
#include "bst.h"
#include <iostream>

int main() {
    Node* root = nullptr;

    wordStruct w1 = {"maca", {1, 2}};
    wordStruct w2 = {"banana", {3}};
    wordStruct w3 = {"laranja", {2, 4}};
    root = insert(root, w1);
    root = insert(root, w2);
    root = insert(root, w3);

    Node* result = treeSearch(root, "maca");
    if (result) {
        std::cout << "Palavra encontrada: " << result->word << "\nDocumentos: ";
        for (int id : result->documentIds) {
            std::cout << id << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Palavra nao encontrada.\n";
    }

    return 0;
}