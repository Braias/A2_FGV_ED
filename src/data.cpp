#include "data.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

namespace dataHandling{
    std::vector<std::string> read_directory(const std::string &dir_path){
        // Cria um vetor de strings para o nome dos arquivos
        std::vector<std::string> files;
        // Itera sobre todos os arquivos do diretorio
        for (const auto& entry : std::filesystem::directory_iterator(dir_path)){
            if (entry.is_regular_file()) {
            // Se o arquivo 
            files.push_back(entry.path().filename().string());
            }
        }
        return files;
    }

    document load_read_doc(const std::string &doc_path, int documentId){
        
    }

}
