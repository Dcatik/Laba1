#include <iostream>
#include <exception>
#include "Matrix.h"
#include "TXTFileReader.h"
#include "TXTFileWriter.h"
#include "CSVFileReader.h"
#include "CSVFileWriter.h"

int main() {
    try {
        // Инициализация объектов для работы с файлами
        TXTFileReader txtReader;
        TXTFileWriter txtWriter;
        CSVFileWriter csvWriter;
        CSVFileReader csvReader;

        // Чтение матрицы A из текстового файла
        Matrix matrixA(txtReader, "matrix_a.txt");
        std::cout << "Matrix A:" << std::endl;
        matrixA.PrintMatrix();

        // Чтение матрицы B из текстового файла
        Matrix matrixB(txtReader, "matrix_b.txt");
        std::cout << "\nMatrix B:" << std::endl;
        matrixB.PrintMatrix();

        // Чтение матрицы C из текстового файла
        Matrix matrixC(txtReader, "matrix_c.txt");
        std::cout << "\nMatrix C:" << std::endl;
        matrixC.PrintMatrix();

        // Чтение матрицы D из CSV файла
        Matrix matrixD(csvReader, "matrix_d.csv");
        std::cout << "\nMatrix D:" << std::endl;
        matrixD.PrintMatrix();

        // Сложение матриц C и D
        std::cout << "\nMatrix C + D:" << std::endl;
        Matrix sumMatrix = matrixC.Add(matrixD);
        sumMatrix.PrintMatrix();

        // Умножение матриц C и D
        std::cout << "\nMatrix C * D:" << std::endl;
        Matrix multMatrix = matrixC.Multiply(matrixD);
        multMatrix.PrintMatrix();

        // Транспонирование результата умножения матриц
        std::cout << "\nTransposed matrix C * D:" << std::endl;
        multMatrix.Transpose().PrintMatrix();

        // Запись матрицы E из текстового файла в CSV формат
        Matrix(txtReader, "matrix_E.txt").WriteToFile(csvWriter, "matrix_E.csv");
        Matrix(txtReader, "matrix_F.txt").WriteToFile(csvWriter, "matrix_F.csv");

        // Чтение матриц E и F из CSV файлов и умножение их
        Matrix matrixE_csv(csvReader, "matrix_E.csv");
        Matrix matrixF_csv(csvReader, "matrix_F.csv");
        std::cout << "\nMatrix E * F from CSV:" << std::endl;
        Matrix multMatrixA_CSV = matrixE_csv.Multiply(matrixF_csv);
        multMatrixA_CSV.PrintMatrix();

        // Умножение матриц E и F, считанных из текстовых файлов
        std::cout << "\nMatrix E * F:" << std::endl;
        Matrix multMatrixA = Matrix(txtReader, "matrix_E.txt").Multiply(Matrix(txtReader, "matrix_F.txt"));
        multMatrixA.PrintMatrix();

        // Вычисление определителя для матриц A, B и C
        std::cout << "\nDeterminant of Matrix A: " << matrixA.GetDeterminant() << std::endl;
        std::cout << "\nDeterminant of Matrix B: " << matrixB.GetDeterminant() << std::endl;
        std::cout << "\nDeterminant of Matrix C: " << matrixC.GetDeterminant() << std::endl;

        // Запись матриц A и D в файлы
        matrixA.WriteToFile(txtWriter, "matrix_A_written.txt");
        matrixC.WriteToFile(csvWriter, "matrix_D.csv");

        // Вычисление обратной матрицы для A
        std::cout << "\nInverse of Matrix A:" << std::endl;
        Matrix inverseA = matrixA.Inverse();
        inverseA.PrintMatrix();

        // Операции с матрицей E
        std::cout << "\nMatrix E: " << std::endl;
        Matrix(txtReader, "matrix_E.txt").PrintMatrix();
        Matrix matrixE = Matrix(txtReader, "matrix_E.txt") * 3;
        std::cout << "\nMatrix E * 3: " << std::endl;
        matrixE.PrintMatrix();

        // Умножение матриц E и F
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
