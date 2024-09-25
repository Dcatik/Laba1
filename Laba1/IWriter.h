#pragma once
#include <vector>
#include <string>

class IWriter {
public:
    virtual void write(const std::string& fileName, const std::vector<std::vector<double>>& matrixData) const = 0;
    virtual ~IWriter() = default;
};