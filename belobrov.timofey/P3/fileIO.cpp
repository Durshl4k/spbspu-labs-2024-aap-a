#include "fileIO.hpp"
#include <fstream>
#include <stdexcept>

void loadMatrix(std::istream& in, int* matrix, size_t rows, size_t cols) {
  for (size_t i = 0; i < rows * cols; ++i) {
    if (!(in >> matrix[i])) {
      throw std::runtime_error("Invalid matrix data")
    }
  }
}

void saveMatrix(const std::string& filename, const int matrix, size_t rows, size_t cols) {
  std::ofstream outFile(filename);
  if (!outFile) {
    throw std::runtime_error("Cannot open output file");
  }
  outFile << rows << " " << cols << "\n";
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      outFile << matrix[i * cols + j] << " ";
    }
  }
}