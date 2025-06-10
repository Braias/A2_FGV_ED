#include <iostream>
#include <string>
#include <vector>
#include "bst.h"
#include "data.h"
#include "tree_utils.h"

using namespace std;

vector<string> collect_file_paths(string path, int limit) { 
    vector<string> file_paths = DataHandling::read_directory(path,limit); // vetor de caminhos para cada documento

    if (file_paths.empty()) { // verificar e avisar se vetor estiver vazio
        cout << "Nenhum arquivo adequado encontrado no diretorio." << endl;
    }
    return file_paths; 
}

BinaryTree* construct_bst(vector<string> file_paths) {  
    int doc_id = 0;
    BinaryTree* bst = create();

    for (size_t path_index = 0; path_index < file_paths.size(); path_index++) { // Itera sobre cada documento do diretorio

        string file_content = DataHandling::load_doc(file_paths.at(path_index)); // extrai seu conteudo

        DataHandling::Document doc = DataHandling::read_doc(file_paths.at(path_index), doc_id, file_content); // segementa strings unicos
        vector<DataHandling::WordAppearance> word_appearances = DataHandling::process_doc(doc); // compila strongs unicos em wordAppearnces

        for (size_t appearance_index = 0; appearance_index < word_appearances.size(); appearance_index++) { // itera sobre cada appearnce
            DataHandling::WordAppearance new_node = word_appearances.at(appearance_index);
            BST::insert(bst, new_node.word, new_node.document_id); // inseri word appearnce como no na BST
        }

        doc_id++; // incrementa doc_id para apos completar processamento
    }
    return bst; // retornar arovre preenchida
}

void perform_search(BinaryTree* bst) {
    // toma input do usuario
    string search_word;

    cout << "Insira a palavra que voce procura: ";
    cin >> search_word;

    // rodar busca em bst
    SearchResult sr = search(bst, search_word); 

    // compilar resumo do search
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

    if(argc != 4){ // verificar contagem certa de instrucoes 
        cout << "Numero insuficiente de Argumentos!";
        return 0;
    }

    else{

        string mode = argv[1];
        int n_docs = stoi(argv[2]); // transformacao de string para int
        string directory_path = argv[3];
        BinaryTree* bst;

        // execucao de search mode
        if(mode == "search"){
            cout << "----------PROCURANDO DOCUMENTOS----------\n";

            if(n_docs <= 0 ){
                cout << n_docs << " - numero de documnentos invalido";
                return 0;  
            }
            
            // construir bst baseado em parametros da recebidos pela CLI
            vector<string> doc_paths = collect_file_paths(directory_path, n_docs);
            bst = construct_bst(doc_paths);

            cout << "Arvore contruida com sucesso\n";
            cout <<"# documentos: " << n_docs << " caminho: "<< directory_path << "\n";
            // Executar busca
            perform_search(bst);
        }
    }
}
