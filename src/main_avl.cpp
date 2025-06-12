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
    vector<string> file_paths = DataHandling::read_directory(path,limit); // Vetor de caminhos para cada documento

    if (file_paths.empty()) { // Verificar e avisar se o vetor estiver vazio
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

        string file_content = DataHandling::load_doc(file_paths.at(path_index)); // Extrai o conteudo do documento
        double time = 0.0;
        int comparisons = 0;
        DataHandling::Document doc = DataHandling::read_doc(file_paths.at(path_index), doc_id, file_content); // Segmenta strings unicos
        vector<DataHandling::WordAppearance> word_appearances = DataHandling::process_doc(doc); // Compila strings unicos em wordAppearances
        
        for (size_t appearance_index = 0; appearance_index < word_appearances.size(); appearance_index++) { // Itera sobre cada word appearance
            DataHandling::WordAppearance new_node = word_appearances.at(appearance_index);
            InsertResult inserts = insert(avl, new_node.word, new_node.document_id); // Insere word appearance como nó na AVL
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
        
        // Incrementa contadores após completar processamento
        totalComparisons += comparisons;
        totalTime += time;
        doc_id++;
    }
    
    // Preenche informações da árvore
    result.totalComparisons = totalComparisons;
    result.comparisonsAVG = totalComparisons / file_paths.size();
    result.totalInsertionTime = totalTime;
    result.insertionTimeAVG = totalTime / file_paths.size();
    result.tree = avl;
    return result; // Retorna arvore preenchida
}

SearchResult perform_search(BinaryTree* avl, string search_word = "") {
    // Recebe input do usuario
    bool default_passed = true;
    if(search_word == ""){
        cout << "Insira a palavra que voce procura: ";
        cin >> search_word;
        default_passed = false;
    }
    
    // Performa busca em avl
    SearchResult sr = search(avl, search_word); 
    
    // Compila resumo do search
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

vector<double> get_search_stats(BinaryTree* avl, const vector<string>& unique_words) {
    // Se não houverem palavras, retorna um vetor vazio
    if (unique_words.empty()) {
        return {0.0, 0.0, 0.0, 0.0};
    }

    // Inicializa stats relevantes
    double word_count = unique_words.size();
    double max_time = 0.0;
    double total_time = 0.0;
    double total_comparisons = 0.0;

    for (const auto& word : unique_words) {
        SearchResult search_result = perform_search(avl, word);
        total_time += search_result.executionTime;
        total_comparisons += search_result.numComparisons;
        // Atualiza tempo maximo de exec 
        if (search_result.executionTime > max_time) {
            max_time = search_result.executionTime;
        }
    }
    //Retorna conjunto de estatiscas para busca
    return {total_time / word_count,max_time,total_comparisons / word_count,total_comparisons};
}

int main(int argc, char* argv[]) {
    
    if(argc != 4){ // Verifica contagem certa de parâmetros 
        cout << "Numero insuficiente de Argumentos!";
        return 0;
    }
    
    else{
        
        string mode = argv[1];
        int n_docs = stoi(argv[2]); // Transformacao de string para int
        string directory_path = argv[3];
        BinaryTree* avl;
        
        //Execucao de search mode
        if(mode == "search"){
            cout << "----------PROCURANDO DOCUMENTOS----------\n";

            if(n_docs <= 0 ){
                cout << n_docs << " - numero de documentos invalidos";
                return 0;  
            }
            
            // Constrói AVL baseado em parametros da recebidos pela CLI
            vector<string> doc_paths = collect_file_paths(directory_path, n_docs);
            avl = construct_avl(doc_paths).tree;
            
            cout << "Arvore construida com sucesso\n";
            cout <<"# documentos: " << n_docs << " caminho: "<< directory_path << "\n";
            // Executa busca
            perform_search(avl);
        }

        if (mode == "stats"){
            cout << "----------ESTATISTICAS----------\n";
            
            if(n_docs <= 0 ){
                cout << n_docs << " - numero de documentos invalidos";
                return 0;
            }

            cout << "----------Insercao----------\n";
            
            // Constrói AVL baseado em parametros da recebidos pela CLI
            vector<string> doc_paths = collect_file_paths(directory_path, n_docs);
            ConstructResult cr = construct_avl(doc_paths);
            BinaryTree* tree = cr.tree;
            
            // Computa estatísticas relevantes
            double avgTime = cr.insertionTimeAVG;
            double avgComp = cr.comparisonsAVG;
            double totalTime = cr.totalInsertionTime;
            int totalComp = cr.totalComparisons;
            
            // Printa todas as estatísticas
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
