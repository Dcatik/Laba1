#pragma once
#include "IReader.h"

class CSVFileReader : public IReader {
public:
    std::vector<std::vector<double>> read(const std::string& fileName) const override;
};