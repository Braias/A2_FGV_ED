#include <iostream>
#include <string>
#include <vector>
#include "bst.h"
#include "data.h"

using namespace std;

vector<string> collect_input() {
    string path;
    cout << "Insira caminho para diretorio contendo documentos: ";
    cin >> path;

    vector<string> file_paths = DataHandling::read_directory(path);
    if (file_paths.empty()) {
        cout << "Nenhum arquivo adequado encontrado no diretorio." << endl;
    }
    return file_paths;
}

BinaryTree* construct_bst(vector<string> file_paths) {
    int doc_id = 0;
    BinaryTree* bst = BST::create();

    for (size_t path_index = 0; path_index < file_paths.size(); path_index++) {
        string file_content = DataHandling::load_doc(file_paths.at(path_index));

        DataHandling::Document doc = DataHandling::read_doc(file_paths.at(path_index), doc_id, file_content);
        vector<DataHandling::WordAppearance> word_appearances = DataHandling::process_doc(doc);

        for (size_t appearance_index = 0; appearance_index < word_appearances.size(); appearance_index++) {
            DataHandling::WordAppearance new_node = word_appearances.at(appearance_index);
            BST::insert(bst, new_node.word, new_node.document_id);
        }

        doc_id++;
    }
    return bst;
}

void perform_search(BinaryTree* bst) {
    string search_word;

    cout << "Insira a palavra que voce procura: ";
    cin >> search_word;

    SearchResult sr = BST::search(bst, search_word);

    if (sr.found) {
        int count = 0;
        size_t index = 0;
        bool continue_searching = true;

        cout << "A palavra '" << search_word << "' foi encontrada nos seguintes docuemntos: " << endl;

        while (continue_searching && index < sr.documentIds.size()) {
            cout << sr.documentIds[index] << " ";
            count++;
            index++;

            if (count == 10) {
                cout << "\nQuer que retorne todos os documentos restantes? (y/n): ";
                char user_input;
                cin >> user_input;

                if (user_input == 'n' || user_input == 'N') {
                    continue_searching = false;
                }
            }
        }

        cout << endl;

    } else {
        cout << "A palavra '" << search_word << "' nao foi encontrada." << endl;
    }

    cout << "# de comapracoes: " << sr.numComparisons << endl;
    cout << "Tempo de exec: " << sr.executionTime << " segundos" << endl;
}


int main() {
    vector<string> file_paths = collect_input();
    if (file_paths.empty()) {
        return 0;  
    }
    BinaryTree* bst = construct_bst(file_paths);
    perform_search(bst);
    BST::destroy(bst);
    return 1;
}
