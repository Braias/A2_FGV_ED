#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "avl.h"
#include "data.h"
#include "tree_utils.h"

using namespace std;
using namespace AVL;

vector<string> collect_file_paths(string path, int limit) { 
    vector<string> file_paths = DataHandling::read_directory(path,limit); // vetor de caminhos para cada documento

    if (file_paths.empty()) { // verificar e avisar se vetor estiver vazio
        cout << "Nenhum arquivo adequado encontrado no diretorio." << endl;
    }
    return file_paths; 
}



ConstructResult construct_avl(vector<string> file_paths) {  
    ConstructResult result;
    BinaryTree* avl = create();
    int doc_id = 0;
    double totalTime = 0.0;
    int totalComparisons = 0;

    for (size_t path_index = 0; path_index < file_paths.size(); path_index++) { // Itera sobre cada documento do diretorio

        string file_content = DataHandling::load_doc(file_paths.at(path_index)); // extrai seu conteudo
        double time = 0.0;
        int comparisons = 0;
        DataHandling::Document doc = DataHandling::read_doc(file_paths.at(path_index), doc_id, file_content); // segementa strings unicos
        vector<DataHandling::WordAppearance> word_appearances = DataHandling::process_doc(doc); // compila strongs unicos em wordAppearnces

        for (size_t appearance_index = 0; appearance_index < word_appearances.size(); appearance_index++) { // itera sobre cada appearnce
            DataHandling::WordAppearance new_node = word_appearances.at(appearance_index);
            InsertResult inserts = insert(avl, new_node.word, new_node.document_id); // inseri word appearnce como no na AVL
            time += inserts.executionTime;
            comparisons += inserts.numComparisons;
            bool found = false;
            
            for (const auto& name : result.unique_words) {
                if (name == new_node.word) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                result.unique_words.push_back(new_node.word);
            }
        };
        
        totalComparisons += comparisons;
        totalTime += time;
        doc_id++; // incrementa doc_id para apos completar processamento
    }

    result.totalComparisons = totalComparisons;
    result.comparisonsAVG = totalComparisons / file_paths.size();
    result.totalInsertionTime = totalTime;
    result.insertionTimeAVG = totalTime / file_paths.size();
    result.tree = avl;
    return result; // retornar arovre preenchida
}

void perform_search(BinaryTree* avl) {
    // toma input do usuario
    string search_word;

    cout << "Insira a palavra que voce procura: ";
    cin >> search_word;

    // rodar busca em avl
    SearchResult sr = search(avl, search_word); 

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

    cout << "# de comparacoes: " << sr.numComparisons << endl;
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
        BinaryTree* avl;

        // execucao de search mode
        if(mode == "search"){
            cout << "----------PROCURANDO DOCUMENTOS----------\n";

            if(n_docs <= 0 ){
                cout << n_docs << " - numero de documentos invalidos";
                return 0;  
            }
            
            // construir bst baseado em parametros da recebidos pela CLI
            vector<string> doc_paths = collect_file_paths(directory_path, n_docs);
            avl = construct_avl(doc_paths).tree;

            cout << "Arvore construida com sucesso\n";
            cout <<"# documentos: " << n_docs << " caminho: "<< directory_path << "\n";
            // Executar busca
            perform_search(avl);
        }

        if (mode == "stats"){
            cout << "----------ESTATISTICAS----------\n";

            if(n_docs <= 0 ){
                cout << n_docs << " - numero de documentos invalidos";
                return 0;
            }

            cout << "----------Inserção----------\n";

            // construir AVL baseado em parametros da recebidos pela CLI
            vector<string> doc_paths = collect_file_paths(directory_path, n_docs);
            ConstructResult cr = construct_avl(doc_paths);
            BinaryTree* tree = cr.tree;

            double avgTime = cr.insertionTimeAVG;
            double avgComp = cr.comparisonsAVG;
            double totalTime = cr.totalInsertionTime;
            int totalComp = cr.totalComparisons;

            cout << "Tempo medio: " << avgTime << "\n";
            cout << "Tempo total: " << totalTime << "\n";
            cout << "Numero medio de comparacoes: " << avgComp << "\n";
            cout << "Numero total de comparacoes: " << totalComp << "\n";

            cout << "----------Busca----------\n";
            cout << "----------Estrutura----------\n";

            int treeHeight = get_tree_height(tree);
            int shortestPath = get_shortest_path(tree);
            int longestPath = treeHeight;

            cout << "Altura da arvore: " << treeHeight << "\n";
            cout << "Tamanho do menor galho (caminho mais curto): " << shortestPath << "\n";
            cout << "Tamanho do maior galho (caminho mais longo): " << longestPath << "\n";


        }
    }
}
