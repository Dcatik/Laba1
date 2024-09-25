#include <iostream>
#include <stdexcept>  // для обработки исключений
#include "matrix.h"
#include "CSVFileReader.h"
#include "CSVFileWriter.h"
#include "TXTFileReader.h"
#include "TXTFileWriter.h"

int main() {
    try {
        TXTFileReader txtReader;
        TXTFileWriter txtWriter;
        CSVFileWriter csvWriter;
        CSVFileReader csvReader;

        Matrix matrixA(txtReader, "matrix_a.txt");
        std::cout << "Matrix A:" << std::endl;
        matrixA.PrintMatrix();

        Matrix matrixB(txtReader, "matrix_b.txt");
        std::cout << "\nMatrix B:" << std::endl;
        matrixB.PrintMatrix();

        Matrix matrixC(txtReader, "matrix_c.txt");
        std::cout << "\nMatrix C:" << std::endl;
        matrixC.PrintMatrix();

        Matrix matrixD(csvReader, "matrix_d.csv");
        std::cout << "\nMatrix D:" << std::endl;
        matrixD.PrintMatrix();

        std::cout << "\nMatrix C+D:" << std::endl;
        Matrix sumMatrix = matrixC.Add(matrixD);
        sumMatrix.PrintMatrix();

        std::cout << "\nMatrix C*D:" << std::endl;
        Matrix multMatrix = matrixC.Multiply(matrixD);
        multMatrix.PrintMatrix();

        std::cout << "\n Transposed matrix C*D: " << std::endl;
        multMatrix.Transpose().PrintMatrix();

        Matrix(txtReader, "matrix_E.txt").WriteToFile(csvWriter, "matrix_E.csv");
        Matrix(txtReader, "matrix_F.txt").WriteToFile(csvWriter, "matrix_F.csv");
        Matrix matrix_E_csv(csvReader, "matrix_E.csv");
        Matrix matrix_F_csv(csvReader, "matrix_F.csv");
        std::cout << "\nMatrix E*F from CSV:" << std::endl;
        Matrix multMatrixA_CSV = matrix_E_csv.Multiply(matrix_F_csv);
        multMatrixA_CSV.PrintMatrix();

        std::cout << "\nMatrix E*F:" << std::endl;
        Matrix multMatrixA = Matrix(txtReader, "matrix_E.txt").Multiply(Matrix(txtReader, "matrix_F.txt"));
        multMatrixA.PrintMatrix();

        std::cout << "\nDeterminant of Matrix A: " << matrixA.GetDeterminant() << std::endl;
        std::cout << "\nDeterminant of Matrix B: " << matrixB.GetDeterminant() << std::endl;
        std::cout << "\nDeterminant of Matrix C: " << matrixC.GetDeterminant() << std::endl;

        matrixA.WriteToFile(txtWriter, "matrix_A_wroten.txt");
        matrixC.WriteToFile(csvWriter, "matrix_D.csv");

        std::cout << "\nInverse of Matrix A:" << std::endl;
        Matrix inverseA = matrixA.Inverse();
        inverseA.PrintMatrix();

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

    return 0;
}
