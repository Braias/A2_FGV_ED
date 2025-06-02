#include "data.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;

namespace dataHandling{
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

}
