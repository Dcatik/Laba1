#include "matrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

Matrix::Matrix()
    : rowCount(0), columnCount(0), matrixData(1, std::vector<double>(1, 0)),
    determinant(0), isDeterminantValid(false) {
}
Matrix::Matrix(int rowCount, int columnCount)
    : rowCount(rowCount), columnCount(columnCount),
    matrixData(rowCount, std::vector<double>(columnCount, 0)),
    determinant(0), isDeterminantValid(false) {
}
Matrix::Matrix(const IReader& reader, const std::string& fileName)
    : Matrix() {  // Delegate to default constructor
    matrixData = reader.read(fileName);
    rowCount = matrixData.size();
    columnCount = rowCount > 0 ? matrixData[0].size() : 0;
    isDeterminantValid = false;
}
Matrix::Matrix(const Matrix& other)
    : rowCount(other.rowCount), columnCount(other.columnCount),
    matrixData(other.matrixData), determinant(other.determinant),
    isDeterminantValid(other.isDeterminantValid) {
}
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

int Matrix::GetRowCount() { return rowCount; }
int Matrix::GetColumnCount() { return columnCount; }

void Matrix::PrintMatrix() {
    for (const auto& row : matrixData) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
}

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
void Matrix::updateDeterminant() {
    determinant = calculateDeterminant(matrixData, columnCount);
    isDeterminantValid = true;
}
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
            return 0.0;
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

    const double epsilon = 1e-9;
    if (std::fabs(det) < epsilon) {
        return 0.0;
    }

    if (swaps % 2 != 0) {
        det = -det;
    }

    return det;
}

std::vector<std::vector<double>> Matrix::getMinor(int row, int col) {
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

Matrix Matrix::Inverse() {
    double det = GetDeterminant();

    const double epsilon = 1e-9;
    if (std::abs(det) < epsilon) {
        throw std::runtime_error("Cannot calculate inverse of matrix with determinant 0.");
    }

    Matrix result(rowCount, columnCount);

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            auto minorMatrix = getMinor(i, j);
            double minorDet = calculateDeterminant(minorMatrix, rowCount - 1);
            result.matrixData[i][j] = ((i + j) % 2 == 1 ? -minorDet : minorDet);
        }
    }
    result = result.Transpose();

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            result.matrixData[i][j] /= det;
        }
    }

    return result;
}

void Matrix::WriteToFile(const IWriter& writer, const std::string& fileName) {
    writer.write(fileName, matrixData);
}
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