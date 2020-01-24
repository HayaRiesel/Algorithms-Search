#pragma once
#include "Searcheable.h"



/*
function DFS(Start, Goal)
Color(Start, Grey)
if Start = Goal
return True
for Child in Expand(Node)
if not Colored(Child)
if DFS(Child, Goal) = True
return True
Color(Start, Black)
return False
*/
template <class T>
class DFS : public Searcher<T> {

    bool dfs(Searcheable<T>* searcheable, vector<State<T>> &answerPath, State<T>* start) {
        this->countState++;
        start->getColor() = grey;
        if (searcheable->isGoalState(start)) {
            //answerPath.insert(answerPath.begin(),*start);
            return true;
        }
        vector<State<T>*> childs = searcheable->getAllPossibleStates(start);
        //for Child in Expand(Node)
        for (int i = 0; i < childs.size(); i++) {
            //if not Colored(Child)
            if (childs[i]->getColor() == white) {
                //  if DFS(Child, Goal) = True
                if (dfs(searcheable, answerPath,childs[i]) == true) {
                    answerPath.insert(answerPath.begin(), *childs[i]);
                    return true;
                }
            }
        }
        //  Color(Start, Black)
        start->getColor() = black;
        //return False
        return false;
    }

public:
    vector<State<T>> Search(Searcheable<T>*  searcheable) {
        vector<State<T>> answerPath;
        State<T>* start = searcheable->getInitialState();
        bool result = dfs(searcheable, answerPath,start);
        if (result == false) {
            answerPath.clear();
            return answerPath;
        }
        answerPath.insert(answerPath.begin(), *start);

        searcheable->initSearcheable();

        return answerPath;
    }


};