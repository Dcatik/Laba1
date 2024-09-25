#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <stdexcept>
#include "CSVFileReader.h"

std::vector<std::vector<double>> CSVFileReader::read(const std::string& fileName) const {
    std::ifstream inputFile(fileName);
    assert(!fileName.empty());
    std::vector<std::vector<double>> matrixData;

    if (inputFile.is_open()) {
        std::string line;

        // Чтение первой строки с количеством строк и столбцов
        if (std::getline(inputFile, line)) {
            std::stringstream ss(line);
            std::string item;
            int rowCount = 0, columnCount = 0;

            if (std::getline(ss, item, ';')) {
                rowCount = std::stoi(item); // Читаем количество строк
            }
            if (std::getline(ss, item, ';')) {
                columnCount = std::stoi(item); // Читаем количество столбцов
            }

            if (rowCount <= 0 || columnCount <= 0) {
                throw std::runtime_error("Error: Invalid row or column count in file " + fileName);
            }

            // Резервируем место для данных матрицы
            matrixData.resize(rowCount);

            // Чтение строк данных матрицы
            for (int i = 0; i < rowCount && std::getline(inputFile, line); ++i) {
                std::stringstream lineStream(line);
                int col = 0;
                while (std::getline(lineStream, item, ';')) {
                    if (col >= columnCount) {
                        throw std::runtime_error("Error: Too many elements in row " + std::to_string(i + 1) + " in file " + fileName);
                    }

                    try {
                        matrixData[i].push_back(std::stod(item)); // Преобразуем строку в double
                    }
                    catch (const std::invalid_argument& e) {
                        throw std::runtime_error("Error: Invalid number at row " + std::to_string(i + 1) + " column " + std::to_string(col + 1) + " in file " + fileName);
                    }

                    col++;
                }

                if (col != columnCount) {
                    throw std::runtime_error("Error: Incorrect number of elements in row " + std::to_string(i + 1) + " column " + std::to_string(col + 1) + " in file " + fileName);
                }
            }

            // Дополнительная проверка на лишние строки
            if (std::getline(inputFile, line) && !line.empty()) {
                throw std::runtime_error("Error: File " + fileName + " contains more data than expected.");
            }
        }

        inputFile.close();
    }
    else {
        throw std::runtime_error("Error: Failed to open file " + fileName);
    }

    return matrixData;
}
