#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <queue>
#include <string>

#include <cstdio>
#include <fstream>
#include <vector>

using namespace std;
using json = nlohmann::json;

class Different {
public:
    static std::queue<std::string> jsonToQueue(const json& jsonArray);
    static std::string ReadFileToString(const std::string& filePath);
};