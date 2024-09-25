#pragma once
#include <vector>
#include <string>

class IReader {
public:
    virtual std::vector<std::vector<double>> read(const std::string& fileName) const = 0;
    virtual ~IReader() = default;
};