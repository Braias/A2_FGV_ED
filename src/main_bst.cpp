#include <iostream>
#include <string>
#include <vector>
#include "bst.h"
#include "data.h"

using namespace std;

vector<string> collect_file_paths(string path, int limit) {
    vector<string> file_paths = DataHandling::read_directory(path,limit);
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
        cout << "A palavra '" << search_word << "' foi encontrada nos seguintes docuemntos: " << endl;
        for(int id : sr.documentIds){
            cout << id << " ";
        }  
        cout << endl;

    } else {
        cout << "A palavra '" << search_word << "' nao foi encontrada." << endl;
    }

    cout << "# de comapracoes: " << sr.numComparisons << endl;
    cout << "Tempo de exec: " << sr.executionTime << " segundos" << endl;
}


int main(int argc, char* argv[]) {
    // vector<string> file_paths = collect_input();
    // if (file_paths.empty()) {
    //     return 0;  
    // }
    // BinaryTree* bst = construct_bst(file_paths);
    // perform_search(bst);
    // BST::destroy(bst);
    // return 1;
    // ./<arvore> search <n_docs> <diretório>
    // ./<arvore> stats <n_docs> <diretório>

    if(argc != 4){
        cout << "Numero insuficiente de Argumentos!";
        return 0;
    }
    else{
        string mode = argv[1];
        int n_docs = stoi(argv[2]);
        string directory_path = argv[3];
        BinaryTree* bst;
        if(mode == "search"){
            cout << "----------PROCURANDO DOCUMENTOS----------\n";

            if(n_docs <= 0 ){
                cout << n_docs << " - numero de documnentos invalido";
                return 0;  
            }
            vector<string> doc_paths = collect_file_paths(directory_path, n_docs);
            bst = construct_bst(doc_paths);

            cout << "Arvore contruida com sucesso\n";
            cout <<"# documentos: " << n_docs << " caminho: "<< directory_path << "\n";

            perform_search(bst);
        }
    }
}
