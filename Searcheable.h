#pragma once
#include <string>
#include <vector>
#include <iterator>
#include "Matrix.h"

using namespace std;

enum color { black , grey , white  };

template <class T>
class State {
private:
    color Color;
    State<T>* father;
    vector<State<T>*> Neighbors;
    T Weight;
    T cumulativeCost;

public:

    pair<int, int> matrixPlace;

    State<T> (T Weight1) {
        Color = white;
        Weight = Weight1;
    }
    State<T>(T Weight1,pair<int,int> matrixplace1) {
        Color = white;
        Weight = Weight1;
        matrixPlace = matrixplace1;
    }

    void addNeighbour(State<T>* st) {
        Neighbors.push_back(st);
    }
    color& getColor() {
        return Color;
    }
    void setFather(State<T>* s) {
        father = s;
    }
    State<T>* getFather() {
        return father;
    }
    int getWeight() const {
        return Weight;
    }
    vector<State<T>*> getNeighbors() {
        return Neighbors;
    }
    int compare(State<T>* s2) {
        if (s2 == this) {
            return true;
        }
    }
    void setCumulativeCost(T num) {
        cumulativeCost = num;
    }
    T getCumulativeCost() const{
        return cumulativeCost;
    }

};

template <class T>
class Searcheable {
public:
    virtual State<T>* getInitialState() = 0;
    virtual bool isGoalState(State<T>*) = 0;
    virtual State<T>* getGoalState() = 0;
    virtual vector<State<T>*> getAllPossibleStates(State<T>*) = 0;
    virtual void initSearcheable() = 0;
};


template <class T>
class Graph :  public Searcheable<T> {
private:
    vector<State<T>*> allVertices;
    State<T>* initialV;
    State<T>* goalV;
    vector<vector<State<T>*>> stateMatritza;

public:

    //n row m Columns
    Graph(Matrix<T> matrix) {
        int n = matrix.shape.size();
        int m = matrix.shape[0].size();
        for (int i = 0; i < n; i++) {
            vector<State<T>*> newLine;
            stateMatritza.push_back(newLine);
            for (int j = 0; j < m; j++) {
                State<T>* v = new State<T>(matrix.shape[i][j], { i,j });
                stateMatritza[i].push_back(v);
                allVertices.push_back(v);
            }
        }
        this->initialV = stateMatritza[matrix.start.first][matrix.start.second];
        this->goalV = stateMatritza[matrix.goal.first][matrix.goal.second];


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                //no neibours
                if (stateMatritza[i][j]->getWeight() == -1) {
                    continue;
                }
                if (!(j + 1 >= m)) {
                    stateMatritza[i][j]->addNeighbour(stateMatritza[i][j + 1]);
                }

                if (!(i - 1 < 0)) {
                    stateMatritza[i][j]->addNeighbour(stateMatritza[i - 1][j]);

                }
                if (!(i + 1 >= n)) {
                    stateMatritza[i][j]->addNeighbour(stateMatritza[i + 1][j]);
                }
                if (!(j - 1 < 0)) {
                    stateMatritza[i][j]->addNeighbour(stateMatritza[i][j - 1]);
                }
            }
        }
    }
    State<T>* getInitialState() {
        return initialV;
    }
    State<T>* getGoalState() {
        return goalV;
    }
    bool isGoalState(State<T>* v) {
        if(this->goalV == v){
            return true;
        }
        return false;
    }
    vector<State<T>*>  getAllPossibleStates(State<T>* v) {
        return v->getNeighbors();
    }

    void initSearcheable() {
        for (int i = 0; i < allVertices.size(); i++) {
            allVertices[i]->getColor() = white;
            allVertices[i]->setFather(nullptr);
            allVertices[i]->setCumulativeCost(NULL);
        }
    }
};