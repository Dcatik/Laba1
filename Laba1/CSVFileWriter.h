#pragma once
#include "IWriter.h"

class CSVFileWriter : public IWriter {
public:
    void write(const std::string& fileName, const std::vector<std::vector<double>>& matrixData) const override;
};
