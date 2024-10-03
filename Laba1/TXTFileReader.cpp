#include <fstream>
#include <stdexcept>
#include "TXTFileReader.h"

std::vector<std::vector<double>> TXTFileReader::read(const std::string& fileName) const {
    if (fileName.empty()) {
        throw std::runtime_error("Error: File name is empty.");
    }
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + fileName);
    }

    std::vector<std::vector<double>> matrixData;
    int rowCount = 0, columnCount = 0;
    inputFile >> rowCount >> columnCount;

    if (rowCount <= 0 || columnCount <= 0) {
        throw std::runtime_error("Error: Invalid row or column count in file " + fileName);
    }
    matrixData.resize(rowCount);
    for (int i = 0; i < rowCount; ++i) {
        std::vector<double> row;
        double value;
        int col = 0;
        while (col < columnCount) {
            if (!(inputFile >> value)) {
                throw std::runtime_error("Error: Not enough data in row " + std::to_string(i + 1) + " in file " + fileName);
            }
            row.push_back(value);
            col++;
        }
        matrixData[i] = row;
    }
    std::string line;
    if (std::getline(inputFile, line) && !line.empty()) {
        throw std::runtime_error("Error: File " + fileName + " contains more data than expected.");
    }

    return matrixData;
}
