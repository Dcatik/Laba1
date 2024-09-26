#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "matrix.h"
#include "CSVFileReader.h"
#include "CSVFileWriter.h"
#include "TXTFileReader.h"
#include "TXTFileWriter.h"

int main() {
    try {
        TXTFileReader txtReader;
        CSVFileWriter csvWriter;
        CSVFileReader csvReader;
        std::vector<Matrix> matrices;
        for (int size = 5; size <= 25; size += 5) {
            for (int i = 1; i <= 10; ++i) {
                std::string fileName = "matrixes/matrix_" + std::to_string(size) + "x" + std::to_string(size) + "_" + std::to_string(i) + ".txt";
                matrices.emplace_back(txtReader, fileName);
                std::cout << "\nMatrix " << i << " (" << size << "x" << size << "):" << std::endl << std::endl;
                matrices.back().PrintMatrix();
                std::cout << "Determinant: " << matrices.back().GetDeterminant() << std::endl;
            }
        }
        if (matrices.size() >= 2) {
            std::cout << "\nDeterminant of Matrix 1: " << matrices[0].GetDeterminant() << std::endl;
            std::cout << "\nDeterminant of Matrix 2: " << matrices[1].GetDeterminant() << std::endl;
            std::cout << "\nInverse of Matrix 1:" << std::endl;
            Matrix inverseA = matrices[0].Inverse();
            inverseA.PrintMatrix();
        }

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

    return 0;
}
