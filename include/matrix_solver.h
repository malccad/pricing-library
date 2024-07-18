#ifndef MATRIX_SOLVER_H
#define MATRIX_SOLVER_H
#include <vector>
#include <map>
#include <string>

std::map<std::string, std::vector<double>> triDiagonalDecomposition(
    const std::map<std::string, std::vector<double>>& triDiagonalMatrix
);

std::vector<double> lowerDiagonalMatrixSolver(
    const std::vector<double>& target,
    const std::vector<double>& diag,
    const std::vector<double>& subDiag
);

std::vector<double> upperDiagonalMatrixSolver(
    const std::vector<double>& target,
    const std::vector<double>& diag,
    const std::vector<double>& superDiag
);

std::vector<double> triDiagonalSolver(
    const std::vector<double> target,
    const std::map<std::string, std::vector<double>>& triDiagonalMatrix
);

#endif