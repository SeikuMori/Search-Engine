// main.cpp
#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main() {
    try {
        ConverterJSON converter;
        InvertedIndex index;

        // Получаем документы и обновляем базу
        auto docs = converter.GetTextDocuments();
        index.UpdateDocumentBase(docs);

        // Получаем запросы и обрабатываем их
        auto requests = converter.GetRequests();
        SearchServer searchServer(index);
        auto results = searchServer.search(requests);

        // Выводим результаты поиска
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << "Request " << i + 1 << ":\n";
            for (const auto& result : results[i]) {
                std::cout << "  Document ID: " << result.doc_id << ", Rank: " << result.rank << "\n";
            }
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
