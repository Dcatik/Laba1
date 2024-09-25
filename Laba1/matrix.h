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
    double determinant;  // ��� �������� ������������
    bool isDeterminantValid; // ���� ��� ��������, ������������ �� �����������

    double calculateDeterminant(const std::vector<std::vector<double>>& matrix, int size) const;
    void updateDeterminant(); // ����� ��� ���������� ������������

    std::vector<std::vector<double>> getMatrixData() const;
    Matrix add(const Matrix& other) const;
    Matrix multiply(const Matrix& other) const;
    Matrix multiplyByScalar(double scalar) const;
    Matrix inverse() const;

public:
    Matrix();
    Matrix(int rowCount, int columnCount);
    Matrix(const IReader& reader, const std::string& fileName); // Dependency on IReader abstraction
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    int GetRowCount() const;
    int GetColumnCount() const;
    void PrintMatrix() const;

    Matrix Add(const Matrix& other) const;
    Matrix Multiply(const Matrix& other) const;
    Matrix MultiplyByScalar(double scalar) const;
    Matrix Transpose() const;
    double GetDeterminant() const;
    Matrix Inverse() const;

    void WriteToFile(const IWriter& writer, const std::string& fileName) const; // Dependency on IWriter abstraction

    ~Matrix();
};
