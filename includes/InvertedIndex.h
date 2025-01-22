// InvertedIndex.h
#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

struct Entry {
    size_t doc_id;
    size_t count;

    // Оператор сравнения для тестов
    bool operator==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {
public:
    InvertedIndex() = default;

    // Метод обновления базы документов
    void UpdateDocumentBase(const std::vector<std::string>& input_docs);

    // Метод получения частоты вхождений слова в документах
    std::vector<Entry> GetWordCount(const std::string& word) const;

private:
    std::vector<std::string> docs;  // Список текстовых документов
    std::map<std::string, std::vector<Entry>> freq_dictionary;  // Частотный словарь
};
