#ifndef dataHandling
#define dataHandling

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace dataHandling{
    struct document{
        int id;
        std::string name;
        std::string content;
    };

    struct processedWord {
        std::string word;
        int documentId;      
    };

    std::vector<std::string> read_directory(const std::string &dir_path){

    };
    
    document load_read_doc(const std::string &doc_path, int documentId){

    };

    std::string process_word(const std::string &word){

    };

    std::vector<processedWord> process_doc(const document &doc){

    };
    
    std::vector<std::vector<processedWord>> inverted_index(){

    };

}


#endif