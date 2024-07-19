#include "JsonFunctions.h"



std::queue<std::string> Different::jsonToQueue(const json& jsonArray) {
    std::queue<std::string> resultQueue;

    if (jsonArray.is_array()) {
        for (const auto& element : jsonArray) {
            if (element.is_string()) {
                resultQueue.push(element.get<std::string>());
            }
        }
    }

    return resultQueue;
}

std::string Different::ReadFileToString(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string fileContents;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            fileContents += line + "\n";
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }

    return fileContents;
}
