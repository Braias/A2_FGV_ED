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

    vector<string> read_directory(const string &dir_path);
    string load_doc(const string &doc_path);
    Document read_doc(const string &doc_path, int document_id);

    vector<WordAppearance> process_doc(const Document &doc);
    InvertedIndex inverted_index(vector<WordAppearance> &word_vector);

}

#endif