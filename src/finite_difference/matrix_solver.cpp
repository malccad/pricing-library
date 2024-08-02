#include "../../include/finite_difference/matrix_solver.h"

std::map<std::string, std::vector<double>> triDiagonalDecomposition(
    const std::map<std::string, std::vector<double>>& triDiagonalMatrix
){
    
    int dim = triDiagonalMatrix.at("diag").size();

    std::vector<double> rightSuperDiag(triDiagonalMatrix.at("superDiag"));
    std::vector<double> rightDiag(dim);
    std::vector<double> leftSubDiag(dim-1);
    std::vector<double> leftDiag(dim, 1);

    rightDiag[0] = triDiagonalMatrix.at("diag")[0];
    
    for (int i=0; i<dim-1; ++i){
        leftSubDiag[i] = triDiagonalMatrix.at("subDiag")[i]/rightDiag[i];
        rightDiag[i+1] = triDiagonalMatrix.at("diag")[i+1] - leftSubDiag[i]*rightSuperDiag[i];
    }

    std::map<std::string, std::vector<double>> decomposed;

    decomposed["rightSuperDiag"] = rightSuperDiag;
    decomposed["rightDiag"] = rightDiag;
    decomposed["leftSubDiag"] = leftSubDiag;
    decomposed["leftDiag"] = leftDiag;

    return decomposed;
}

std::vector<double> lowerDiagonalMatrixSolver(
    const std::vector<double>& target,
    const std::vector<double>& diag,
    const std::vector<double>& subDiag
){
    int dim = diag.size();
    std::vector<double> out(dim);

    out[0] = target[0]/diag[0];
    for (int i =1; i<dim; ++i){
        out[i] = (target[i] - subDiag[i-1]*out[i-1])/diag[i];
    }
    return out;
}

std::vector<double> upperDiagonalMatrixSolver(
    const std::vector<double>& target,
    const std::vector<double>& diag,
    const std::vector<double>& superDiag
){
    int dim = diag.size();
    std::vector<double> out(dim);

    out[dim-1] = target[dim-1]/diag[dim-1];
    for (int i=dim-2; i>=0; --i){
        out[i] = (target[i]-superDiag[i]*out[i+1])/diag[i];
    }
    return out;
}

std::vector<double> triDiagonalSolver(
    const std::vector<double> target,
    const std::map<std::string, std::vector<double>>& triDiagonalMatrix
){
    std::map<std::string, std::vector<double>> decomposed = triDiagonalDecomposition(triDiagonalMatrix);
    std::vector<double> w = lowerDiagonalMatrixSolver(
        target,
        decomposed.at("leftDiag"),
        decomposed.at("leftSubDiag")
    );
    std::vector<double> v = upperDiagonalMatrixSolver(
        w,
        decomposed.at("rightDiag"),
        decomposed.at("rightSuperDiag")
    );
    return v;
}

