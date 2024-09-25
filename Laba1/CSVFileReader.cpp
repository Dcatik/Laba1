#include <fstream>
#include <stdexcept>
#include "CSVFileReader.h"

std::vector<std::vector<double>> CSVFileReader::read(const std::string& fileName) const {
    std::ifstream inputFile(fileName);
    if (fileName.empty()) {
        throw std::runtime_error("Error: File name is empty.");
    }

    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Failed to open file " + fileName);
    }

    std::vector<std::vector<double>> matrixData;
    std::string line;

    // Чтение первой строки с количеством строк и столбцов
    if (std::getline(inputFile, line)) {
        int rowCount = 0;
        int columnCount = 0;
        std::string item;
        size_t pos = 0;

        // Чтение количества строк
        pos = line.find(';');
        if (pos != std::string::npos) {
            rowCount = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);  // Удаляем прочитанное количество строк
        }

        // Чтение количества столбцов
        columnCount = std::stoi(line);

        if (rowCount <= 0 || columnCount <= 0) {
            throw std::runtime_error("Error: Invalid row or column count in file " + fileName);
        }

        // Резервируем место для данных матрицы
        matrixData.resize(rowCount);

        // Чтение строк данных матрицы
        for (int i = 0; i < rowCount && std::getline(inputFile, line); ++i) {
            int col = 0;
            size_t start = 0;
            size_t end;

            while ((end = line.find(';', start)) != std::string::npos) {
                if (col >= columnCount) {
                    throw std::runtime_error("Error: Too many elements in row " + std::to_string(i + 1) + " in file " + fileName);
                }

                // Извлечение значения
                item = line.substr(start, end - start);
                start = end + 1;

                // Преобразуем строку в double
                try {
                    matrixData[i].push_back(std::stod(item));
                }
                catch (const std::invalid_argument& e) {
                    throw std::runtime_error("Error: Invalid number at row " + std::to_string(i + 1) + " column " + std::to_string(col + 1) + " in file " + fileName);
                }

                col++;
            }

            // Проверка на последнее значение в строке (после последней точки с запятой)
            if (start < line.size()) {
                item = line.substr(start);
                if (col >= columnCount) {
                    throw std::runtime_error("Error: Too many elements in row " + std::to_string(i + 1) + " in file " + fileName);
                }
                try {
                    matrixData[i].push_back(std::stod(item));
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
    return matrixData;
}
