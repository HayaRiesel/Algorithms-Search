#pragma once

/*
Best-First-Search( Maze m )
    Insert( m.StartNode )
    Until PriorityQueue is empty
        c <- PriorityQueue.DeleteMin
        If c is the goal
            Exit
        Else
            Foreach neighbor n of c
                If n "Unvisited"
                    Mark n "Visited"
                    Insert( n )
            Mark c "Examined"
End procedure
*/

#include "Searcheable.h"
#include "Searcher.h"
#include <queue>
#include <functional>
#include <vector>
#include <iostream>
#include <map>

//the compare for the q
template <class T>
class mycomparison{
    bool reverse;
public:
    mycomparison(const bool& revparam = false)
    {
        reverse = revparam;
    }
    bool operator() (const State<T>* s1, const State<T>* s2) const
    {
        if (reverse) return (s1->getCumulativeCost() < s2->getCumulativeCost());
        else return (s1->getCumulativeCost() > s2->getCumulativeCost());
    }
};

template <class T>
class BestFirstSearch : public Searcher<T> {
public:

    void bestfirstSearch(Searcheable<T>*  searcheable)
    {
        State<T>* start = searcheable->getInitialState();
        start->setCumulativeCost(start->getWeight());
        priority_queue<State<T>*, vector<State<T>*>, mycomparison<T>> pq;
        pq.push(start);
        while (!pq.empty()) {
            this->countState++;
            State<T>* u = pq.top();
            pq.pop();
            if (searcheable->isGoalState(u)) {
                return;
            }
            vector<State<T>*> childs = searcheable->getAllPossibleStates(u);
            for (int i = 0; i < childs.size(); i++) {
                if (childs[i]->getColor() == white) {
                    childs[i]->setCumulativeCost(u->getCumulativeCost()+childs[i]->getWeight());
                    childs[i]->setFather(u);
                    childs[i]->getColor() = grey;
                    pq.push(childs[i]);
                }
            }
            u->getColor() = black;
        }
    }

    void addFather(vector<State<T>>& answerPath, State<T>* v) {
        State<T>* father = v->getFather();
        if (father == nullptr) {
            return;
        }
        answerPath.insert(answerPath.begin(), *father);
        addFather(answerPath, father);
    }

    vector<State<T>> Search(Searcheable<T>*  searcheable) {
        vector<State<T>> answerPath;
        bestfirstSearch(searcheable);
        if (searcheable->getGoalState()->getFather() == nullptr) {
            return answerPath;
        }
        answerPath.push_back(*(searcheable->getGoalState()));
        addFather(answerPath, searcheable->getGoalState());
        searcheable->initSearcheable();
        return answerPath;
    }

};