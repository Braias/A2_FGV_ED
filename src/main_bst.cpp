#include <iostream>
#include <string>
#include <vector>
#include "bst.h"
#include "data.h"

int main(){
    string path;
    std::cout<<"Insere caminho para documentos a serem processados: ";
    std::cin >> path;
    vector<string> file_paths = DataHandling::read_directory(path);
    std::cout << "Directory is empty (1/0): " << file_paths.empty();
}