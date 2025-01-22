// SearchServer.cpp
#include "SearchServer.h"
#include <algorithm>
#include <map>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    std::vector<std::vector<RelativeIndex>> result;

    for (const auto& query : queries_input) {
        std::map<size_t, float> doc_relevance;

        // Разбиваем запрос на слова и считаем релевантность документов
        std::istringstream stream(query);
        std::string word;
        while (stream >> word) {
            for (const auto& entry : _index.GetWordCount(word)) {
                doc_relevance[entry.doc_id] += entry.count;
            }
        }

        // Преобразуем карту в вектор и нормализуем ранги
        std::vector<RelativeIndex> sorted_results;
        float max_relevance = 0;
        for (const auto& [doc_id, relevance] : doc_relevance) {
            max_relevance = std::max(max_relevance, relevance);
        }

        for (const auto& [doc_id, relevance] : doc_relevance) {
            sorted_results.push_back({doc_id, relevance / max_relevance});
        }

        // Сортируем по убыванию релевантности
        std::sort(sorted_results.begin(), sorted_results.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
            return b.rank < a.rank;
        });

        result.push_back(sorted_results);
    }

    return result;
}
