#pragma once
#include "IReader.h"

class TXTFileReader : public IReader {
public:
    std::vector<std::vector<double>> read(const std::string& fileName) const override;
};