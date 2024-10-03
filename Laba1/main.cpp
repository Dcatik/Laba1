#include <iostream>
#include <exception>
#include "Matrix.h"
#include "TXTFileReader.h"
#include "TXTFileWriter.h"
#include "CSVFileReader.h"
#include "CSVFileWriter.h"

int main() {
    try {
        // ������������� �������� ��� ������ � �������
        TXTFileReader txtReader;
        TXTFileWriter txtWriter;
        CSVFileWriter csvWriter;
        CSVFileReader csvReader;

        // ������ ������� A �� ���������� �����
        Matrix matrixA(txtReader, "matrix_a.txt");
        std::cout << "Matrix A:" << std::endl;
        matrixA.PrintMatrix();

        // ������ ������� B �� ���������� �����
        Matrix matrixB(txtReader, "matrix_b.txt");
        std::cout << "\nMatrix B:" << std::endl;
        matrixB.PrintMatrix();

        // ������ ������� C �� ���������� �����
        Matrix matrixC(txtReader, "matrix_c.txt");
        std::cout << "\nMatrix C:" << std::endl;
        matrixC.PrintMatrix();

        // ������ ������� D �� CSV �����
        Matrix matrixD(csvReader, "matrix_d.csv");
        std::cout << "\nMatrix D:" << std::endl;
        matrixD.PrintMatrix();

        // �������� ������ C � D
        std::cout << "\nMatrix C + D:" << std::endl;
        Matrix sumMatrix = matrixC.Add(matrixD);
        sumMatrix.PrintMatrix();

        // ��������� ������ C � D
        std::cout << "\nMatrix C * D:" << std::endl;
        Matrix multMatrix = matrixC.Multiply(matrixD);
        multMatrix.PrintMatrix();

        // ���������������� ���������� ��������� ������
        std::cout << "\nTransposed matrix C * D:" << std::endl;
        multMatrix.Transpose().PrintMatrix();

        // ������ ������� E �� ���������� ����� � CSV ������
        Matrix(txtReader, "matrix_E.txt").WriteToFile(csvWriter, "matrix_E.csv");
        Matrix(txtReader, "matrix_F.txt").WriteToFile(csvWriter, "matrix_F.csv");

        // ������ ������ E � F �� CSV ������ � ��������� ��
        Matrix matrixE_csv(csvReader, "matrix_E.csv");
        Matrix matrixF_csv(csvReader, "matrix_F.csv");
        std::cout << "\nMatrix E * F from CSV:" << std::endl;
        Matrix multMatrixA_CSV = matrixE_csv.Multiply(matrixF_csv);
        multMatrixA_CSV.PrintMatrix();

        // ��������� ������ E � F, ��������� �� ��������� ������
        std::cout << "\nMatrix E * F:" << std::endl;
        Matrix multMatrixA = Matrix(txtReader, "matrix_E.txt").Multiply(Matrix(txtReader, "matrix_F.txt"));
        multMatrixA.PrintMatrix();

        // ���������� ������������ ��� ������ A, B � C
        std::cout << "\nDeterminant of Matrix A: " << matrixA.GetDeterminant() << std::endl;
        std::cout << "\nDeterminant of Matrix B: " << matrixB.GetDeterminant() << std::endl;
        std::cout << "\nDeterminant of Matrix C: " << matrixC.GetDeterminant() << std::endl;

        // ������ ������ A � D � �����
        matrixA.WriteToFile(txtWriter, "matrix_A_written.txt");
        matrixC.WriteToFile(csvWriter, "matrix_D.csv");

        // ���������� �������� ������� ��� A
        std::cout << "\nInverse of Matrix A:" << std::endl;
        Matrix inverseA = matrixA.Inverse();
        inverseA.PrintMatrix();

        // �������� � �������� E
        std::cout << "\nMatrix E: " << std::endl;
        Matrix(txtReader, "matrix_E.txt").PrintMatrix();
        Matrix matrixE = Matrix(txtReader, "matrix_E.txt") * 3;
        std::cout << "\nMatrix E * 3: " << std::endl;
        matrixE.PrintMatrix();

        // ��������� ������ E � F
        matrixE = Matrix(txtReader, "matrix_E.txt") * Matrix(txtReader, "matrix_F.txt");
        std::cout << "\nMatrix E * F: " << std::endl;
        matrixE.PrintMatrix();
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "File error: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Matrix operation error: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }

    return 0;
}
