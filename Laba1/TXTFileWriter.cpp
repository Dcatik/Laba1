#include <fstream>
#include <cassert>
#include <iostream>
#include "TXTFileWriter.h"

void TXTFileWriter::write(const std::string& fileName, const std::vector<std::vector<double>>& matrixData) const {
    std::ofstream outputFile(fileName);
    assert(!fileName.empty());
    if (outputFile.is_open()) {
        // ������� ���������� ����� � ��������
        size_t numRows = matrixData.size();
        size_t numCols = matrixData.empty() ? 0 : matrixData[0].size();
        outputFile << numRows << " " << numCols << "\n";

        // ������� �������� �������
        for (const auto& row : matrixData) {
            for (const auto& element : row) {
                outputFile << element << " ";
            }
            outputFile << "\n";
        }
        outputFile.close();
        assert(outputFile.good());
    }
    else {
        std::cerr << "Error opening file: " << fileName << "\n";
    }
}
