#include <cmath>
#include "../../include/monte_carlo/linear_algebra.h"

std::vector<std::vector<double>> getGramMatrix(const std::vector<std::vector<double>>& X){
    unsigned long numCols = X[0].size();
    unsigned long numRows = X.size();
    std::vector<std::vector<double>> gramMatrix;
    for (int i=0; i<numCols; ++i){
        std::vector<double> curRow;
        for (int j=0; j<numCols; ++j){
            double z = 0.0;
            for (int k=0; k< numRows; ++k){
                z += X[k][i]*X[k][j];
            }
            curRow.push_back(z);
        }
        gramMatrix.push_back(curRow);
    }
    return gramMatrix;
}

std::vector<std::vector<double>> invertPosSymDefMat(const std::vector<std::vector<double>>& M){
    std::vector<std::vector<double>> L = choleskyDecomposition(M);
    std::vector<std::vector<double>> L_inv = invertLowerTriangularMatrix(L);
    std::vector<std::vector<double>> L_inv_tran = transpose(L_inv);
    std::vector<std::vector<double>> M_inv = matMul(L_inv_tran, L_inv);
    return M_inv;
}

std::vector<std::vector<double>> choleskyDecomposition(const std::vector<std::vector<double>>& A){
    std::vector<std::vector<double>> L;
    for (int i=0; i<A.size(); ++i){
        std::vector<double> curRow;
        // subdiagonal
        for (int j=0; j<i; ++j){
            double x = A[i][j];
            for (int k=0; k<j; ++k){
                x -= (curRow[k]*L[j][k]);
            }
            x /= L[j][j];
            curRow.push_back(x);
        }
        // diagonal
        double x = A[i][i];
        for (int k=0; k<i; ++k){
            x -= curRow[k]*curRow[k];
        }
        curRow.push_back(sqrt(x));
        // superdiagonal
        for (int j=i+1; j<A.size(); ++j){
            curRow.push_back(0.0);
        }
        L.push_back(curRow);
    }
    return L;
}

std::vector<std::vector<double>> invertLowerTriangularMatrix(const std::vector<std::vector<double>>& L){
    std::vector<std::vector<double>> M;
    for (int i=0; i<L.size(); ++i){
        std::vector<double> curRow;
        // subdiagonal
        for (int j=0; j<i; ++j){
            double x = 0.0;
            for (int k=j; k<i; ++k){
                x -= L[i][k]*M[k][j];
            }
            x /= L[i][i];
            curRow.push_back(x);
        }
        // diagonal
        curRow.push_back(1/L[i][i]);
        // superdiagonal
        for (int j=i+1; j<L.size(); ++j){
            curRow.push_back(0.0);
        }
        M.push_back(curRow);
    }
    return M;
}

std::vector<std::vector<double>> matMul(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B
){
    assert (A[0].size() == B.size());
    std::vector<std::vector<double>> M;
    for (int i=0; i<A.size(); ++i){
        std::vector<double> curRow;
        for (int j=0; j<B[0].size(); ++j){
            double x = 0.0;
            for (int k=0; k<B.size(); ++k){
                x += A[i][k]*B[k][j];
            }
            curRow.push_back(x);
        }
        M.push_back(curRow);
    }
    return M;
}
double dotProduct(const std::vector<double>& v1, const std::vector<double>& v2){
    assert (v1.size() == v2.size());
    double x = 0.0;
    for (int i=0; i<v1.size(); ++i){
        x += v1[i]*v2[i];
    }
    return x;
}

std::vector<double> matMulVector(
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& v
){
    assert (A[0].size() == v.size());
    std::vector<double> b;
    for (int i=0; i<A.size(); ++i){
        double x = dotProduct(A[i], v);
        b.push_back(x);
    }
    return b;
}

std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& M){
    std::vector<std::vector<double>> M_tran;
    for (int i=0; i<M[0].size(); ++i){
        std::vector<double> curRow;
        for (int j=0; j<M.size(); ++j){
            curRow.push_back(M[j][i]);
        }
        M_tran.push_back(curRow);
    }
    return M_tran;
}