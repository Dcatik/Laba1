#include "matrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

// Default constructor
Matrix::Matrix()
    : rowCount(0), columnCount(0), matrixData(1, std::vector<double>(1, 0)),
    determinant(0), isDeterminantValid(false) {}

// Parameterized constructor
Matrix::Matrix(int rowCount, int columnCount)
    : rowCount(rowCount), columnCount(columnCount),
    matrixData(rowCount, std::vector<double>(columnCount, 0)),
    determinant(0), isDeterminantValid(false) {}

// Reading constructor
Matrix::Matrix(const IReader& reader, const std::string& fileName)
    : Matrix() {  // Delegate to default constructor
    matrixData = reader.read(fileName);
    rowCount = matrixData.size();
    columnCount = rowCount > 0 ? matrixData[0].size() : 0;
    isDeterminantValid = false;
}

// Copy constructor
Matrix::Matrix(const Matrix& other)
    : rowCount(other.rowCount), columnCount(other.columnCount),
    matrixData(other.matrixData), determinant(other.determinant),
    isDeterminantValid(other.isDeterminantValid) {}

// Assignment operator overload
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        rowCount = other.rowCount;
        columnCount = other.columnCount;
        matrixData = other.matrixData;
        determinant = other.determinant;
        isDeterminantValid = other.isDeterminantValid;
    }
    return *this;
}

// Get row count
int Matrix::GetRowCount() { return rowCount; }

// Get column count
int Matrix::GetColumnCount() { return columnCount; }

// Print matrix
void Matrix::PrintMatrix() {
    for (const auto& row : matrixData) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
}

// Scalar multiplication
Matrix Matrix::MultiplyByScalar(double scalar) {
    Matrix result(*this);
    for (auto& row : result.matrixData) {
        for (auto& elem : row) {
            elem *= scalar;
        }
    }
    result.isDeterminantValid = false;
    return result;
}

// Transpose matrix
Matrix Matrix::Transpose() {
    Matrix result(columnCount, rowCount);
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            result.matrixData[j][i] = matrixData[i][j];
        }
    }
    result.isDeterminantValid = false;
    return result;
}

// Addition of matrices
Matrix Matrix::Add(const Matrix& other) {
    if (rowCount != other.rowCount || columnCount != other.columnCount) {
        throw std::invalid_argument("Error: Matrices must be of the same size for addition.");
    }

    Matrix result(rowCount, columnCount);
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            result.matrixData[i][j] = matrixData[i][j] + other.matrixData[i][j];
        }
    }
    result.isDeterminantValid = false;
    return result;
}

// Multiplication of matrices
Matrix Matrix::Multiply(const Matrix& other) {
    if (columnCount != other.rowCount) {
        throw std::invalid_argument("Matrices cannot be multiplied: column count of the first matrix does not match row count of the second matrix.");
    }

    Matrix result(rowCount, other.columnCount);
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < other.columnCount; ++j) {
            result.matrixData[i][j] = 0; // Initialize element
            for (int k = 0; k < columnCount; ++k) {
                result.matrixData[i][j] += matrixData[i][k] * other.matrixData[k][j];
            }
        }
    }
    result.isDeterminantValid = false;
    return result;
}

// Update determinant
void Matrix::updateDeterminant() {
    determinant = calculateDeterminant(matrixData, columnCount);
    isDeterminantValid = true;
}

// Get determinant
double Matrix::GetDeterminant() {
    if (!isDeterminantValid) {
        updateDeterminant();
    }
    return determinant;
}


void Matrix::swap(std::vector<double>& a, std::vector<double>& b) {
    std::vector<double> temp = a;
    a = b;
    b = temp;
}
// Calculate determinant using Gaussian elimination
double Matrix::calculateDeterminant(const std::vector<std::vector<double>>& matrix, int size) {
    std::vector<std::vector<double>> mat = matrix;
    double det = 1.0;
    int swaps = 0;

    for (int i = 0; i < size; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < size; ++k) {
            if (std::fabs(mat[k][i]) > std::fabs(mat[maxRow][i])) {
                maxRow = k;
            }
        }

        if (mat[maxRow][i] == 0) {
            return 0.0;  // Determinant is zero
        }

        if (i != maxRow) {
            swap(mat[i], mat[maxRow]);
            ++swaps;
        }

        for (int k = i + 1; k < size; ++k) {
            double factor = mat[k][i] / mat[i][i];
            for (int j = i; j < size; ++j) {
                mat[k][j] -= factor * mat[i][j];
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        det *= mat[i][i];
    }

    // Проверка на epsilon
    const double epsilon = 1e-9; // Можно изменить по необходимости
    if (std::fabs(det) < epsilon) {
        return 0.0;  // Определитель близок к нулю
    }

    // Упрощенный вывод знака детерминанта
    if (swaps % 2 != 0) {
        det = -det; // Меняем знак при нечетном числе перестановок
    }

    return det;
}

std::vector<std::vector<double>> Matrix::GetMinor(int row, int col) {
    std::vector<std::vector<double>> minorMatrix(this->rowCount - 1, std::vector<double>(this->columnCount - 1));
    int di = 0;
    for (int i = 0; i < rowCount - 1; i++) {
        if (i == row) di = 1;
        int dj = 0;
        for (int j = 0; j < columnCount - 1; j++) {
            if (j == col) dj = 1;
            minorMatrix[i][j] = matrixData[i + di][j + dj];
        }
    }
    return minorMatrix;
}

// Обновлённый метод Inverse
Matrix Matrix::Inverse() {
    double det = GetDeterminant();

    const double epsilon = 1e-9; // можно подкорректировать в зависимости от точности вычислений
    if (std::abs(det) < epsilon) {
        throw std::runtime_error("Cannot calculate inverse of matrix with determinant 0.");
    }

    Matrix result(rowCount, columnCount);

    // Вычисление матрицы алгебраических дополнений (миноров)
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            // Получение минора
            auto minorMatrix = GetMinor(i, j);
            // Определитель минора
            double minorDet = calculateDeterminant(minorMatrix, rowCount - 1);
            // Применяем знак (чередование по строкам и столбцам)
            result.matrixData[i][j] = ((i + j) % 2 == 1 ? -minorDet : minorDet);
        }
    }

    // Транспонируем матрицу дополнений
    result = result.Transpose();

    // Делим каждую ячейку на определитель исходной матрицы
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            result.matrixData[i][j] /= det;
        }
    }

    return result;
}

// Write matrix to file
void Matrix::WriteToFile(const IWriter& writer, const std::string& fileName) {
    writer.write(fileName, matrixData);
}

// Destructor
Matrix::~Matrix() {}

Matrix Matrix::operator*(const Matrix& other) {
    return this->Multiply(other);
}

template<typename T>
Matrix Matrix::operator*(T scalar) {
    return this->MultiplyByScalar(scalar);
}

template Matrix Matrix::operator*<int>(int);
template Matrix Matrix::operator*<float>(float);
template Matrix Matrix::operator*<double>(double);
