#include <iostream>
#include <string>
#include <vector>
#include "bst.h"
#include "data.h"
#include "tree_utils.h"

using namespace std;
using namespace BST;

vector<string> collect_file_paths(string path, int limit) { 
    vector<string> file_paths = DataHandling::read_directory(path,limit); // vetor de caminhos para cada documento

    if (file_paths.empty()) { // verificar e avisar se vetor estiver vazio
        cout << "Nenhum arquivo adequado encontrado no diretorio." << endl;
    }
    return file_paths; 
}

ConstructResult construct_bst(vector<string> file_paths) {
    ConstructResult result;
    BinaryTree* bst = create();
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
            InsertResult inserts = insert(bst, new_node.word, new_node.document_id); // inseri word appearnce como no na BST
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
    result.tree = bst;
    return result; // retornar arovre preenchida
}

SearchResult perform_search(BinaryTree* bst, string search_word = "") {
    // toma input do usuario
    bool default_passed = true;
    if(search_word == ""){
        cout << "Insira a palavra que voce procura: ";
        cin >> search_word;
        default_passed = false;
    }

    // rodar busca em bst
    SearchResult sr = search(bst, search_word); 

    // compilar resumo do search
    if(!default_passed){
        if (sr.found ) {
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
    return sr;
}

vector<double> get_search_stats(BinaryTree* bst, const vector<string>& unique_words) {
    if (unique_words.empty()) {
        return {0.0, 0.0, 0.0, 0.0};
    }

    double word_count = unique_words.size();

    double max_time = 0.0;
    double total_time = 0.0;
    double total_comparisons = 0.0;

    for (const auto& word : unique_words) {
        SearchResult search_result = perform_search(bst, word);
        total_time += search_result.executionTime;
        total_comparisons += search_result.numComparisons;
        // Atualizando tempo maximo de exec
        if (search_result.executionTime > max_time) {
            max_time = search_result.executionTime;
        }
    }
    //Retornando conjunto de estatiscas para busca
    return {total_time / word_count,max_time,total_comparisons / word_count,total_comparisons};
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
            bst = construct_bst(doc_paths).tree;

            cout << "Arvore contruida com sucesso\n";
            cout <<"# documentos: " << n_docs << " caminho: "<< directory_path << "\n";
            // Executar busca
            perform_search(bst);
        }

        if (mode == "stats"){
            cout << "----------ESTATISTICAS----------\n";

            if(n_docs <= 0 ){
                cout << n_docs << " - numero de documentos invalidos";
                return 0;
            }

            cout << "----------Insercao----------\n";

            // construir AVL baseado em parametros da recebidos pela CLI
            vector<string> doc_paths = collect_file_paths(directory_path, n_docs);
            ConstructResult cr = construct_bst(doc_paths);
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
            vector<double> search_stats = get_search_stats(tree,cr.unique_words);
            cout << "Tempo medio: " << search_stats.at(0) << "\n";
            cout << "Tempo Maximo: " << search_stats.at(1) << "\n";
            cout << "Numero medio de comparacoes: " << search_stats.at(2) << "\n";
            cout << "Numero total de comparacoes: " << search_stats.at(3) << "\n";


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
