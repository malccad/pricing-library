#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H
#include <vector>

std::vector<std::vector<double>> getGramMatrix(const std::vector<std::vector<double>>& X);
std::vector<std::vector<double>> invertPosSymDefMat(const std::vector<std::vector<double>>& M);
std::vector<std::vector<double>> choleskyDecomposition(const std::vector<std::vector<double>>& A);
std::vector<std::vector<double>> invertLowerTriangularMatrix(const std::vector<std::vector<double>>& L);
std::vector<std::vector<double>> matMul(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B
);
double dotProduct(const std::vector<double>& v1, const std::vector<double>& v2);
std::vector<double> matMulVector(
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& v
);
std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& M);
#endif