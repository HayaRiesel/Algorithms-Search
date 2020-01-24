//
// Created by yaellax on 21/01/2020.
//

#ifndef UNTITLED9_ASTAR_H
#define UNTITLED9_ASTAR_H

#include "Searcheable.h"
#include "Searcher.h"
#include <queue>
#include <functional>
#include <vector>
#include <iostream>
#include <list>
#include <iterator>
#include <map>
#include <set>
#include "DFS.h"
#include <limits>


template <class T>
class Astar : public Searcher<T> {
    vector<State<T>> reconstruct_path(map<State<T>*, State<T>*> cameFrom, State<T>* current) {
        vector<State<T>> total_path;
        //total_path.push_back(*current);
        //current in cameFrom.Keys
        while (cameFrom.find(current) != cameFrom.end()) {
            total_path.insert(total_path.begin(), *current);
            current = cameFrom[current];
        }
        total_path.insert(total_path.begin(), *current);

        return total_path;

    }

    int h(State<T>* current,State<T>* goal) {

        int count=0;
        count += abs(goal->matrixPlace.first - current->matrixPlace.first);
        count += abs(goal->matrixPlace.second - current->matrixPlace.second);
        return count;
    }

    vector<State<T>> aStar(Searcheable<T>*  searcheable){
        State<T>* start = searcheable->getInitialState();
        set<State<T>*> openSet;
        openSet.insert(start);
        map<State<T>*, State<T>*> cameFrom;
        map<State<T>*, T> gScore;
        gScore[start] = 0;
        map<State<T>*, T> fScore;
        fScore[start] = h(start,searcheable->getGoalState());

        openSet.insert(start);
        while (!openSet.empty()) {
            this->countState++;
            State<T>* current;
            current = *(openSet.begin());
            //current := the node in openSet having the lowest fScore[] value
            for (auto it = openSet.begin(); it != openSet.end(); it++) {
                if (fScore[*it] < fScore[current]) {
                    current = (*it);
                }
            }

            if (searcheable->isGoalState(current)) {
                return reconstruct_path(cameFrom, current);
            }
            openSet.erase(current);
            //for each neighbor of current
            vector<State<T>*> childs = searcheable->getAllPossibleStates(current);
            for (int i = 0; i < childs.size(); i++) {
                State<T>* neighbor = childs[i];
                //childs[i]->setFather(current);
                T tentative_gScore = gScore[current] + neighbor->getWeight();
                if ( gScore.find(neighbor) == gScore.end() || tentative_gScore < gScore[neighbor]) {
                    cameFrom[neighbor] = current;
                    if (neighbor->getWeight() == -1) {
                        continue;
                    }

                    gScore[neighbor] = tentative_gScore;
                    fScore[neighbor] = gScore[neighbor] + h(neighbor, searcheable->getGoalState());

                    //if neighbor not in openSet
                    openSet.insert( neighbor );
                }


            }

        }
        vector<State<T>> null;
        return null;

    }


public:
    vector<State<T>> Search(Searcheable<T>*  searcheable) {
        vector<State<T>> answerPath = aStar(searcheable);
        searcheable->initSearcheable();
        return answerPath;
    }
};





/*
function reconstruct_path(cameFrom, current)
total_path : = { current }
    while current in cameFrom.Keys :
        total_path.prepend(current)
        current : = cameFrom[current]
        return total_path

        // A* finds a path from start to goal.
        // h is the heuristic function. h(n) estimates the cost to reach goal from node n.
        function A_Star(start, goal, h)
        // The set of discovered nodes that may need to be (re-)expanded.
        // Initially, only the start node is known.
        openSet : = { start }

        // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start to n currently known.
    cameFrom: = an empty map

        // For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
        gScore : = map with default value of Infinity
        gScore[start] : = 0

        // For node n, fScore[n] := gScore[n] + h(n).
        fScore : = map with default value of Infinity
        fScore[start] : = h(start)

        while openSet is not empty
            current : = the node in openSet having the lowest fScore[] value
            if current = goal
                return reconstruct_path(cameFrom, current)

                openSet.Remove(current)
                for each neighbor of current
                    // d(current,neighbor) is the weight of the edge from current to neighbor
                    // tentative_gScore is the distance from start to the neighbor through current
                    tentative_gScore : = gScore[current] + d(current, neighbor)
                    if tentative_gScore < gScore[neighbor]
                        // This path to neighbor is better than any previous one. Record it!
                        cameFrom[neighbor] : = current
                        gScore[neighbor] : = tentative_gScore
                        fScore[neighbor] : = gScore[neighbor] + h(neighbor)
                        if neighbor not in openSet
                            openSet.add(neighbor)

                            // Open set is empty but goal was never reached
                            return failure

                            */




#endif //UNTITLED9_ASTAR_H
