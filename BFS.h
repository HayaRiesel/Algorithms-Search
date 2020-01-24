#pragma once
#include "Searcheable.h"
#include <queue>


template <class T>
class BFS : public Searcher<T> {
private:
    /*
    1  procedure BFS(G, start_v) is
        2      let Q be a queue
        3      label start_v as discovered
        4      Q.enqueue(start_v)
        5      while Q is not empty do
        6          v : = Q.dequeue()
        7          if v is the goal then
        8              return v
        9          for all edges from v to w in G.adjacentEdges(v) do
        10             if w is not labeled as discovered then
        11                 label w as discovered
        12                 w.parent : = v
        13                 Q.enqueue(w)
*/
    void bfs(Searcheable<T>*  searcheable)
    {
        queue<State<T>*> q;
        State<T>* start = searcheable->getInitialState();
        start->getColor() = grey;
        q.push(start);
        while (!(q.empty())) {
            this->countState++;
            State<T>* v = q.front();
            q.pop();
            if (searcheable->isGoalState(v)) {
                return;
            }
            vector<State<T>*> childs = searcheable->getAllPossibleStates(v);
            for (int i = 0; i < childs.size(); i++) {
                if (childs[i]->getColor() == white) {
                    childs[i]->getColor() = grey;
                    childs[i]->setFather(v);
                    q.push(childs[i]);

                }

            }
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
public:
    vector<State<T>> Search(Searcheable<T>*  searcheable) {
        vector<State<T>> answerPath;
        bfs(searcheable);
        if (searcheable->getGoalState()->getFather() == nullptr) {
            return answerPath;
        }
        answerPath.push_back(*(searcheable->getGoalState()));
        addFather(answerPath, searcheable->getGoalState());
        searcheable->initSearcheable();
        return answerPath;
    }



};