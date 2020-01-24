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

template <class Problem,class Solution>
class MatrixSolver : public Solver<Problem,Solution>{
    Solver<Problem,Solution>* deepCopy(){
        return new MatrixSolver<Problem,Solution>();
    }



    string findPath(vector<State<double>> path) {
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

    Searcher<double>* MySearcher;

    string solveTheProb(Matrix<double> matrix) {
        Searcheable<double >* graph = new Graph<double>(matrix);
        Astar<double> aStar;
        string solution = findPath(aStar.Search(graph));
        return solution;
    }

};




template <class Problem,class Solution>
class StringReverser : public Solver<Problem,Solution>{
    Solver<Problem,Solution>* deepCopy(){
        return new StringReverser<Problem,Solution>();
    }
    string solveTheProb(string input){

        string output;
        int i;
        for (i = input.size() - 1; i >= 0; i--) {
            output = output.append(1, input[i]);
        };
        return output;
    }
};


#endif //UNTITLED9_SOLVER_H
