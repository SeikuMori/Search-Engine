// ConverterJSON.h
#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

class ConverterJSON {
public:
    // Конструктор по умолчанию
    ConverterJSON() = default;

    // Получение списка текстовых документов из config.json
    std::vector<std::string> GetTextDocuments();

    // Получение лимита ответов из config.json
    int GetResponsesLimit();

    // Получение запросов из requests.json
    std::vector<std::string> GetRequests();

    // Запись ответов в файл answers.json
    void putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);

private:
    // Вспомогательный метод для чтения JSON из файла
    nlohmann::json ReadJSON(const std::string& filename);
};
