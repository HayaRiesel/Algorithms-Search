#include <vector>
#pragma once
using namespace std;

template <class T>
class Matrix {
public:
    vector<vector<T>> shape;
    pair<int, int> start;
    pair<int, int> goal;
    int n;
    int m;
    Matrix(vector<vector<T>> shape1, pair<int, int> start1, pair<int, int> goal1) {
        this->shape = shape1;
        this->goal = goal1;
        this->start = start1;
        this->n = shape1.size();
        this->m = shape1[0].size();

    }
    //default start amd goal
    Matrix(vector<vector<T>> shape1) {
        this->shape = shape1;
        this->n = shape1.size();
        this->m = shape1[0].size();
        this->goal = { n-1,m-1 };
        this->start = { 0,0 };

    }
};