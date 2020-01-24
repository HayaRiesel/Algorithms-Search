//
// Created by yaellax on 12/01/2020.
//

#ifndef UNTITLED9_SOLVER_H
#define UNTITLED9_SOLVER_H
#include <ostream>
#include <string>
#include "Searcher.h"
#include "BFS.h"
#include "Matrix.h"
#include "ClientHandler.h"
#include "BestFirstSearch.h"
#include "DFS.h"
#include "Astar.h"
using namespace std;

template <class Problem,class Solution>
class Solver {
public:
virtual Solution solveTheProb(Problem) = 0;
virtual Solver<Problem,Solution>* deepCopy() = 0;

};

//template <class Problem,class Solution>
class MatrixSolver : public Solver<Matrix<double>,string>{
private:
    string findPath(vector<State<double>> path);
    Searcher<double>* MySearcher;
public:
    Solver<Matrix<double>,string>* deepCopy();
    string solveTheProb(Matrix<double> matrix);

};




//template <class Problem,class Solution>
class StringReverser : public Solver<string,string>{
public:
    Solver<string,string>* deepCopy();
    string solveTheProb(string input);

};


#endif //UNTITLED9_SOLVER_H
