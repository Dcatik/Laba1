#include <fstream>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "TXTFileReader.h"

std::vector<std::vector<double>> TXTFileReader::read(const std::string& fileName) const {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Unable to open file " + fileName);
    }

    assert(!fileName.empty());

    std::vector<std::vector<double>> matrixData;
    if (inputFile.is_open()) {
        int rowCount, columnCount;
        inputFile >> rowCount >> columnCount;

        if (rowCount <= 0 || columnCount <= 0) {
            throw std::runtime_error("Error: Invalid row or column count in file " + fileName);
        }

        matrixData.resize(rowCount);

        std::string line;
        std::getline(inputFile, line);  // —читываем оставшуюс€ строку после rowCount и columnCount

        for (int i = 0; i < rowCount; ++i) {
            if (!std::getline(inputFile, line)) {
                throw std::runtime_error("Error: Not enough rows in file " + fileName);
            }

            std::istringstream iss(line);
            double value;
            int col = 0;
            std::vector<double> row;

            while (iss >> value) {
                if (col >= columnCount) {
                    throw std::runtime_error("Error: Too many elements in row " + std::to_string(i + 1) + " in file " + fileName);
                }
                row.push_back(value);
                col++;
            }

            if (col != columnCount) {
                throw std::runtime_error("Error: Incorrect number of elements in row " + std::to_string(i + 1) + " column " + std::to_string(col + 1) + " in file " + fileName);
            }

            matrixData[i] = row;
        }

        // ƒополнительна€ проверка на лишние строки
        if (std::getline(inputFile, line) && !line.empty()) {
            throw std::runtime_error("Error: File " + fileName + " contains more data than expected.");
        }
    }
    else {
        std::cerr << "Failed to open file.\n";
    }

    return matrixData;
}
