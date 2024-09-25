#include "matrix.h"
#include <iostream>
#include <fstream>
#include <cassert>


// TODO: ������� ��������� isDeterminantValid � determinant
// 
// 
// 
// 
// 
// Constructors
//

// default constructor
Matrix::Matrix()
    : rowCount(0), columnCount(0), matrixData(1, std::vector<double>(1, 0)),
    determinant(0), isDeterminantValid(false) {}

// constractor with parameters
Matrix::Matrix(int rowCount, int columnCount)
    : rowCount(rowCount), columnCount(columnCount),
    matrixData(rowCount, std::vector<double>(columnCount, 0)),
    determinant(0), isDeterminantValid(false) {}

// reading constructor
Matrix::Matrix(const IReader& reader, const std::string& fileName) {
    this->matrixData = reader.read(fileName);
    this->rowCount = matrixData.size();
    this->columnCount = matrixData.empty() ? 0 : matrixData[0].size();
    this->determinant = 0;
    this->isDeterminantValid = false;
}

// copying constructor
Matrix::Matrix(const Matrix& other) : rowCount(other.rowCount), columnCount(other.columnCount)
    , matrixData(other.matrixData), determinant(other.determinant), isDeterminantValid(other.isDeterminantValid) {}

// "=" overloading
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

// Get data from matrix
std::vector<std::vector<double>> Matrix::getMatrixData() const {
    return matrixData;
}

int Matrix::GetRowCount() const { return rowCount; }

int Matrix::GetColumnCount() const { return columnCount; }

void Matrix::PrintMatrix() const {
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            std::cout << matrixData[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Operations

Matrix Matrix::multiplyByScalar(double scalar) const {
    Matrix result(*this);
    for (int i = 0; i < result.rowCount; ++i) {
        for (int j = 0; j < result.columnCount; ++j) {
            result.matrixData[i][j] *= scalar;
        }
    }
    result.isDeterminantValid = false;

    return result;
}

Matrix Matrix::MultiplyByScalar(double scalar) const {
    return this->multiplyByScalar(scalar);
}

Matrix Matrix::Transpose() const {
    Matrix result(columnCount, rowCount);
    for (int i = 0; i < rowCount; ++i)
        for (int j = 0; j < columnCount; ++j)
            result.matrixData[j][i] = matrixData[i][j];
    return result;
}

Matrix Matrix::add(const Matrix& other) const {
    // �������� �� ���������� �������� ������
    if (this->rowCount != other.rowCount || this->columnCount != other.columnCount) {
        throw std::invalid_argument("������: ������� ������ ���� ����������� ������� ��� ��������.");
    }

    // ������� ����� ������� ��� �������� ����������
    Matrix result(this->rowCount, this->columnCount);

    // ���������� ��������������� ��������
    for (int i = 0; i < this->rowCount; ++i) {
        for (int j = 0; j < this->columnCount; ++j) {
            result.matrixData[i][j] = this->matrixData[i][j] + other.matrixData[i][j];
        }
    }

    return result;
}
Matrix Matrix::Add(const Matrix& other) const {
    return this->add(other);
}

Matrix Matrix::multiply(const Matrix& other) const {
    // ���������, ��� ��������� ��������
    if (this->columnCount != other.rowCount) {
        throw std::invalid_argument("Matrices cannot be multiplied: column count of the first matrix does not match row count of the second matrix.");
    }

    // ������ ����� ������� ��� �������� ����������
    Matrix result(this->rowCount, other.columnCount);

    // ��������� ��������� ������
    for (int i = 0; i < this->rowCount; ++i) {
        for (int j = 0; j < other.columnCount; ++j) {
            result.matrixData[i][j] = 0; // �������������� ������� �������������� �������
            for (int k = 0; k < this->columnCount; ++k) {
                result.matrixData[i][j] += this->matrixData[i][k] * other.matrixData[k][j];
            }
        }
    }

    return result;
}

Matrix Matrix::Multiply(const Matrix& other) const {
    return this->multiply(other);
}


void Matrix::updateDeterminant() {
    determinant = calculateDeterminant(this->matrixData, this->columnCount); // ��������� �����������
    isDeterminantValid = true; // ������������� ���� ��� ��������������
}

// ����� ��� ��������� ������������
double Matrix::GetDeterminant() const{
    if (!isDeterminantValid) {
        this->updateDeterminant(); // ���� ����������� �� ������������, ��������� ���
    }
    return determinant; // ���������� �������������� ��������
}

double Matrix::calculateDeterminant(const std::vector<std::vector<double>>& matrix, int size) const {
    // ������ ����� ������� ��� �����������
    std::vector<std::vector<double>> mat = matrix;
    double det = 1.0; // ��������� �������� ������������
    int swaps = 0;    // ���������� ������������ �����

    for (int i = 0; i < size; ++i) {
        // ������� ������������ ������� � ������� i ��� ������������ ������
        int maxRow = i;
        for (int k = i + 1; k < size; ++k) {
            if (fabs(mat[k][i]) > fabs(mat[maxRow][i])) {
                maxRow = k;
            }
        }

        // ���� ������������ ������� 0, ����������� ����� 0
        if (mat[maxRow][i] == 0) {
            return 0.0;
        }

        // ������������ �����
        if (i != maxRow) {
            std::swap(mat[i], mat[maxRow]);
            ++swaps;
        }

        // �������� ������� � ����������������� �����
        for (int k = i + 1; k < size; ++k) {
            double factor = mat[k][i] / mat[i][i];
            for (int j = i; j < size; ++j) {
                mat[k][j] -= factor * mat[i][j];
            }
        }
    }

    // ����������� - ��� ������������ ��������� �� ������� ���������
    for (int i = 0; i < size; ++i) {
        det *= mat[i][i];
    }

    // ���� ���� �������� ���������� ������������, ������ ���� ������������
    if (swaps % 2 != 0) {
        det = -det;
    }

    return det;
}



Matrix Matrix::Inverse() const {
    double det = GetDeterminant();
    if (det == 0) {
        throw std::runtime_error("Cannot calculate inverse of matrix with determinant 0.");
    }

    int n = rowCount; // ������������, ��� ������� ����������
    Matrix augmentedMatrix(n, 2 * n); // ����������� �������
    // ���������� ����������� �������
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmentedMatrix.matrixData[i][j] = matrixData[i][j]; // �������� �������
            if (i == j) {
                augmentedMatrix.matrixData[i][j + n] = 1; // ��������� �������
            }
            else {
                augmentedMatrix.matrixData[i][j + n] = 0;
            }
        }
    }

    // ������ ���
    for (int i = 0; i < n; ++i) {
        // ����� ������������� �������� � ������� �������
        double maxEl = fabs(augmentedMatrix.matrixData[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (fabs(augmentedMatrix.matrixData[k][i]) > maxEl) {
                maxEl = fabs(augmentedMatrix.matrixData[k][i]);
                maxRow = k;
            }
        }

        // ������������ �����
        std::swap(augmentedMatrix.matrixData[maxRow], augmentedMatrix.matrixData[i]);

        // ������������ ������� ������
        double divisor = augmentedMatrix.matrixData[i][i];
        for (int j = 0; j < 2 * n; ++j) {
            augmentedMatrix.matrixData[i][j] /= divisor;
        }

        // ��������� ��������� �����
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = augmentedMatrix.matrixData[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    augmentedMatrix.matrixData[k][j] -= factor * augmentedMatrix.matrixData[i][j];
                }
            }
        }
    }

    // ������� �������� �������
    Matrix inverseMatrix(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverseMatrix.matrixData[i][j] = augmentedMatrix.matrixData[i][j + n]; // ���������� ������ ��������
        }
    }

    return inverseMatrix;
}



void Matrix::WriteToFile(const IWriter& writer, const std::string& fileName) const {
    assert(!fileName.empty());
    writer.write(fileName, matrixData);
}

Matrix::~Matrix() {
    // �� �� ��� �� ����� �� � �����, ������� �������� <3
}
