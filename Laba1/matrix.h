#pragma once
#include <vector>
#include <string>
#include "IReader.h"
#include "IWriter.h"

class Matrix {
private:
    int rowCount;
    int columnCount;
    std::vector<std::vector<double>> matrixData;
    double determinant;
    bool isDeterminantValid;

    std::vector<std::vector<double>> getMinor(int row, int col);
    double calculateDeterminant(const std::vector<std::vector<double>>& matrix, int size);
    void updateDeterminant();

    void swap(std::vector<double>& a, std::vector<double>& b);

public:
    Matrix();
    Matrix(int rowCount, int columnCount);
    Matrix(const IReader& reader, const std::string& fileName);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    int GetRowCount();
    int GetColumnCount();
    void PrintMatrix();

    Matrix Add(const Matrix& other);
    Matrix Multiply(const Matrix& other);
    Matrix MultiplyByScalar(double scalar);
    Matrix Transpose();
    double GetDeterminant();
    Matrix Inverse();
    void WriteToFile(const IWriter& writer, const std::string& fileName);

    ~Matrix();

    template<typename T>
    Matrix operator*(T scalar);
    Matrix operator*(const Matrix& other);
};
