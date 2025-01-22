// InvertedIndex.cpp
#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {
    docs = input_docs;
    freq_dictionary.clear();

    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id) {
        std::map<std::string, size_t> word_count;
        std::istringstream stream(docs[doc_id]);
        std::string word;

        // Разбиваем документ на слова
        while (stream >> word) {
            ++word_count[word];
        }

        // Обновляем частотный словарь
        for (const auto& [word, count] : word_count) {
            freq_dictionary[word].push_back({doc_id, count});
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) const {
    if (freq_dictionary.find(word) != freq_dictionary.end()) {
        return freq_dictionary.at(word);
    } else {
        return {};
    }
}
