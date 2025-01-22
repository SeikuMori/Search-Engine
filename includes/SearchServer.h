// SearchServer.h
#pragma once
#include "InvertedIndex.h"

struct RelativeIndex {
    size_t doc_id;
    float rank;

    // Оператор сравнения для тестов
    bool operator==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
    // Конструктор принимает ссылку на инвертированный индекс
    SearchServer(InvertedIndex& idx) : _index(idx) {};

    // Метод обработки поисковых запросов
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex& _index;  // Ссылка на инвертированный индекс
};
