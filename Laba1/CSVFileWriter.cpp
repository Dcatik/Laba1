#include <iostream>
#include <fstream>
#include <cassert>
#include "CSVFileWriter.h"

void CSVFileWriter::write(const std::string& fileName, const std::vector<std::vector<double>>& matrixData) const {
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Error: Unable to write to file " + fileName);
    }
    assert(!fileName.empty());

    if (outputFile.is_open()) {
        // Записываем количество строк и столбцов в первую строку
        size_t numRows = matrixData.size();
        size_t numCols = matrixData.empty() ? 0 : matrixData[0].size();
        outputFile << numRows << ";" << numCols << "\n";  // Используем точку с запятой

        // Записываем содержимое матрицы
        for (const auto& row : matrixData) {
            for (size_t i = 0; i < row.size(); ++i) {
                outputFile << row[i];
                if (i < row.size() - 1) {
                    outputFile << ";";  // Разделяем элементы внутри строки точкой с запятой
                }
            }
            outputFile << "\n";  // Переход на новую строку для каждой строки матрицы
        }
        outputFile.close();
        assert(outputFile.good());
    }
    else {
        std::cerr << "Error opening file: " << fileName << "\n";
    }
}

