//
// Created by yaellax on 16/01/2020.
//
#include "BestFirstSearch.h"
#include "Searcheable.h"
#include "Searcher.h"
#include <iostream>
#include "Astar.h"
#include <map>
#include "DFS.h"
#include "BFS.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


int main() {
    //srand(time(NULL));

    vector<vector<vector<int>>> matrixs;
    int N = 10;
    //matrixs[i][j][k] = rand() % 10 + 1;
    for (int i = 0; i < 10; i++, N += 4) {
        //one matrix
        vector<vector<int>> matrix;
        for (int j = 0; j < N; j++) {
            vector<int> row;
            for (int k = 0; k < N; k++) {
                row.push_back(rand() % 100 - 1);
            }
            matrix.push_back(row);
        }
        matrixs.push_back(matrix);
    }
    vector<pair<int, Searcheable<int>*>> searcheables;
    for (int i = 0; i < matrixs.size(); i++) {


        Matrix<int>* matrix = new Matrix<int>(matrixs[i]);
        Searcheable<int>* graph = new Graph<int>(*(matrix));
        searcheables.push_back({ matrixs[i].size(), graph });
    }
    DFS<int> dfs;
    BFS<int> bfs;
    Astar<int> aStar;
    BestFirstSearch<int> bestFirstSearch;
    //map<string,map<int,double>> results;

    double dfsSum = 0;
    double bfsSum = 0;
    double aStarSum = 0;
    double bestFirstSearchSum = 0;
    for (int i = 0; i < searcheables.size(); i++) {
        dfsSum = dfs.SearcherReturnCountState(searcheables[i].second);
        bfsSum = bfs.SearcherReturnCountState(searcheables[i].second);
        aStarSum = aStar.SearcherReturnCountState(searcheables[i].second);
        bestFirstSearchSum = bestFirstSearch.SearcherReturnCountState(searcheables[i].second);
        cout << searcheables[i].first<< " Astar : " << aStarSum <<" best first search: " << bestFirstSearchSum  <<": dfs: " << dfsSum << " bfs: " << bfsSum << endl;

    }
    int n;
    cin >> n;



    return 1;
}
