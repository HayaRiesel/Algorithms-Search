//
// Created by yaellax on 12/01/2020.
//

#include "Solver.h"


Solver<Matrix<double>, string> * MatrixSolver::deepCopy() {
    return new MatrixSolver();
}
string MatrixSolver::findPath(vector<State<double>> path) {
    string result;
    if (path.empty()) {
        return "there is no way";
    }
    int x = path[0].matrixPlace.second;
    int y = path[0].matrixPlace.first;
    for (int i = 1; i < path.size(); i++) {
        if (path[i].matrixPlace.first < y) {
            result += "Up, ";
        }
        if (path[i].matrixPlace.first > y) {
            result += "Down, ";
        }
        if (path[i].matrixPlace.second > x) {
            result += "Right, ";
        }
        if (path[i].matrixPlace.second < x) {
            result += "Left, ";
        }
        x = path[i].matrixPlace.second;
        y = path[i].matrixPlace.first;
    }
    //remove the ", " from the end
    result = result.substr(0, result.size() - 2);

    return result;

}
string MatrixSolver::solveTheProb(Matrix<double>) {
    Searcheable<double >* graph = new Graph<double>(matrix);
    Astar<double> aStar;
    string solution = findPath(aStar.Search(graph));
    return solution;

}

Solver<string, string> * StringReverser::deepCopy() {
    return new StringReverser();
}
string StringReverser::solveTheProb(string) {
    string output;
    int i;
    for (i = input.size() - 1; i >= 0; i--) {
        output = output.append(1, input[i]);
    };
    return output;
}
