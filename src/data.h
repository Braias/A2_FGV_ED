#ifndef DATA_HANDLING_H
#define DATA_HANDLING_H

#include <string>
#include <vector>

using namespace std;

namespace DataHandling{

    /**
    * @brief Estrutura para documentos e sua identificação
    *
    * Contem uma id única que inicia em 1, nome do arquivo
    * e vetor de palavras únicas que compõem seu conteúdo
    */
    struct Document{
        int id; ///< ID único do documento (começa em 1)
        string name; ///< Caminho completo para o documento
        vector<string> content; ///< Palavras únicas encontradas no documento
    };

    /**
    * @brief Representa uma aparição de uma palavra em um documento
    *
    * Estrutura usada para armazenar os pares (palavra, ID) que podem
    * ser inseridos facilmente na estrura de inverted index.
    */
    struct WordAppearance {
        string word; ///< Palavra encontrada
        vector<int> document_ids; ///< Documentos nos quais foi localizada
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

    /**
    * @brief Organiza as componentes de Document em um vetor de estruturas do tipo WordAppearance
    * @param doc Document a ser transformado em vetor
    * @return Vetor de WordAppearance
    */
    vector<WordAppearance> process_doc(const Document &doc);
}

#endif