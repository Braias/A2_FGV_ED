#include "data.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;

namespace DataHandling{
    vector<string> read_directory(const string &dir_path){
        // Cria um vetor de strings para o nome dos arquivos
        vector<string> files;
        // Itera sobre todos os arquivos do diretorio
        for (const auto& entry : filesystem::directory_iterator(dir_path)){
            if (entry.is_regular_file()) {
            // Se o arquivo 
            files.push_back(entry.path().string());
            }
        }
        return files;
    }

    string load_doc(const string &doc_path){
        ifstream file (doc_path);

        if (!file.is_open()){
            return "";
        }
        
        string content;
        string line;

        while (getline(file, line)){
            content += line;
            content += ' ';
        }
        return content;
    };

    Document read_doc(const string &doc_path, int document_id, string conteudo){
        // Extrai o nome do arquivo do caminho completo
        size_t pos = doc_path.find_last_of("/\\");
        string file_name = doc_path.substr(pos + 1);

        Document doc;
        doc.id = document_id;
        doc.name = file_name;

        // Separação das frases em palavras
        vector<string> words;
        size_t start = 0;
        size_t end = 0;
        
        while (start < conteudo.length()) {
            // Encontra próximo espaço
            end = conteudo.find(' ', start);
            
            // Extrai palavra
            string word = conteudo.substr(start, end - start);
            if (!word.empty()) {
                words.push_back(word);
            }
            
            // Fim da string
            if (end == string::npos) break;
            
            // Avança para próxima palavra
            start = end + 1;
        };
        doc.content = words;
        return doc;
    };

    vector<WordAppearance> process_doc(const Document &doc){
        vector<WordAppearance> word_appearances;

        // Insere palavras
        for (const string& word : doc.content) {
            WordAppearance entry;
            entry.word = word;
            entry.document_ids.push_back(doc.id);
            word_appearances.push_back(entry);
        }
        return word_appearances;
    };
}
