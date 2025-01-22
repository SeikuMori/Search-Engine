// ConverterJSON.cpp
#include "ConverterJSON.h"
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

json ConverterJSON::ReadJSON(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    json j;
    file >> j;
    return j;
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    json config = ReadJSON("config.json");

    if (config.find("config") == config.end()) {
        throw std::runtime_error("Error: config file is empty");
    }

    std::vector<std::string> files;
    for (const auto& file : config["files"]) {
        files.push_back(file);
    }
    return files;
}

int ConverterJSON::GetResponsesLimit() {
    json config = ReadJSON("config.json");
    return config["config"].value("max_responses", 5);
}

std::vector<std::string> ConverterJSON::GetRequests() {
    json requests = ReadJSON("requests.json");

    std::vector<std::string> result;
    for (const auto& request : requests["requests"]) {
        result.push_back(request);
    }
    return result;
}

void ConverterJSON::putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    json output;
    json& answersJSON = output["answers"];

    for (size_t i = 0; i < answers.size(); ++i) {
        std::string requestID = "request" + std::to_string(i + 1);
        if (answers[i].empty()) {
            answersJSON[requestID]["result"] = "false";
        } else {
            answersJSON[requestID]["result"] = "true";
            for (const auto& [docID, rank] : answers[i]) {
                answersJSON[requestID]["relevance"].push_back({{"docid", docID}, {"rank", rank}});
            }
        }
    }

    std::ofstream outFile("answers.json");
    outFile << output.dump(4);  // Сохраняем с форматированием
}
