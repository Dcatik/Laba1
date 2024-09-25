#include <fstream>
#include <iostream>
#include "TXTFileWriter.h"

void TXTFileWriter::write(const std::string& fileName, const std::vector<std::vector<double>>& matrixData) const {
    std::ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        // Output number of rows and columns
        int numRows = matrixData.size();
        int numCols = 0;

        if (numRows > 0) {
            numCols = matrixData[0].size();
        }

        outputFile << numRows << " " << numCols << "\n";

        // Output matrix elements
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                outputFile << matrixData[i][j] << " ";
            }
            outputFile << "\n";
        }

        outputFile.close();
        if (!outputFile.good()) {
            std::cerr << "Error writing to file: " << fileName << "\n";
        }
    }
    else {
        std::cerr << "Error opening file: " << fileName << "\n";
    }
}
