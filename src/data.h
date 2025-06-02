#ifndef DATA_HANDLING_H
#define DATA_HANDLING_H

#include <string>
#include <vector>

using namespace std;

namespace DataHandling{
    struct Document{
        int id;
        string name;
        vector<string> content;
    };

    struct WordAppearance {
        string word;
        int document_id;
    };

    struct InvertedIndex {
        vector<string> words;
        vector<vector<int>> document_ids;
    };

    /**
    * @brief Lê os arquivos do diretório providenciado
    * @param dir_path caminho para o diretório
    * @return Vetor de caminhos para os documentos do diretório
    */
    vector<string> read_directory(const string &dir_path);

    /**
    * @brief Carrega o documento de acordo com o path providenciado
    * @param doc_path caminho para o documento
    * @return String do conteúdo do arquivo
    */
    string load_doc(const string &doc_path);

    /**
    * @brief Lê o conteúdo do doc e gera a estrutura Document, com sua id,
    * seu nome baseado no path e um vetor de strings únicas a partir da string conteúdo
    * @param doc_path caminho para o documento
    * @param document_id id do documento
    * @param conteudo conteúdo do documento
    * @return Estrutura Document contendo um vetor de palavras únicas, nome e ID
    */
    Document read_doc(const string &doc_path, int document_id, string conteudo);

    vector<WordAppearance> process_doc(const Document &doc);
    InvertedIndex inverted_index(vector<WordAppearance> &word_vector);

}

#endif