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
            files.push_back(entry.path().filename().string());
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
        string file_name = (pos == string::npos) ? doc_path : doc_path.substr(pos + 1);

        Document doc;
        doc.id = document_id;
        doc.name = file_name;

        // Tokenização do conteúdo
        vector<string> tokens;
        size_t start = 0;
        size_t end = 0;
        
        while (start < conteudo.length()) {
            // Encontra próximo espaço
            end = conteudo.find(' ', start);
            
            // Extrai token
            string token = conteudo.substr(start, end - start);
            if (!token.empty()) {
                tokens.push_back(token);
            }
            
            // Fim da string
            if (end == string::npos) break;
            
            // Avança para próximo token
            start = end + 1;
        };

        vector<string> unique_tokens;
        for (const string& token : tokens) {
            bool exists = false;
            for (const string& unique : unique_tokens) {
                if (unique == token) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                unique_tokens.push_back(token);
            }
        }
        doc.content = unique_tokens;
        return doc;
    }


}
