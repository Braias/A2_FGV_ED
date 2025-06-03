#include "tree_utils.h"

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

Node* createNode(std::string word) {
    Node* n = new Node();
    n->word = word;
    n->left = nullptr;
    n->right = nullptr;
    n->parent = nullptr;

    return n;
}

Node* insert(Node* root, std::string word, int docID) {
    if (root == nullptr) {
        Node* newNode = createNode(word);
        newNode->documentIds.push_back(docID);
        return newNode;
    };

    if (word < root->word) {
        Node* leftChild = insert(root->left, word, docID);
        root->left = leftChild;
        leftChild->parent = root;
    } else if (word > root->word) {
        Node* rightChild = insert(root->right, word, docID);
        root->right = rightChild;
        rightChild->parent = root;
    } else {
        root->documentIds.push_back(docID);
    }
    return root;
};
