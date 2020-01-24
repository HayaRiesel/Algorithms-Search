#pragma once

#include "Searcheable.h"


template <class T>
class Searcher {
protected:
    int countState = 0;
public:
    virtual vector<State<T>> Search(Searcheable<T>*) = 0;
    virtual T SearcherReturnSum(Searcheable<T>* searcheable) {
        vector<State<T>> answerPath = Search(searcheable);
        T counter = 0;
        for (int i = 0; i < answerPath.size(); i++) {
            counter += answerPath[i].getWeight();
        }
        return counter;
    }
    virtual T SearcherReturnCountState(Searcheable<T>* s) {
        Search(s);
        return countState;
    }

};


