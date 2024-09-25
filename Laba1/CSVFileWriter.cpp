#include <fstream>
#include <stdexcept>
#include "CSVFileWriter.h"

void CSVFileWriter::write(const std::string& fileName, const std::vector<std::vector<double>>& matrixData) const {
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Error: Unable to write to file " + fileName);
    }

    if (fileName.empty()) {
        throw std::runtime_error("Error: File name is empty.");
    }

    // Записываем количество строк и столбцов в первую строку
    int numRows = static_cast<int>(matrixData.size());
    int numCols = (numRows > 0) ? static_cast<int>(matrixData[0].size()) : 0;
    outputFile << numRows << ";" << numCols << "\n";  // Используем точку с запятой

    // Записываем содержимое матрицы
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            outputFile << matrixData[i][j];
            if (j < numCols - 1) {
                outputFile << ";";  // Разделяем элементы внутри строки точкой с запятой
            }
        }
        outputFile << "\n";  // Переход на новую строку для каждой строки матрицы
    }

    outputFile.close();
    if (!outputFile.good()) {
        throw std::runtime_error("Error: Failed to write all data to file " + fileName);
    }
}
