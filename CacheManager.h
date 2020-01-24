#ifndef UNTITLED9_CACHEMANAGER_H
#define UNTITLED9_CACHEMANAGER_H

#include <iostream>


#include <string>
#include <unordered_map>
#include <fstream>
#include<functional>
#include <list>
using namespace std;


template<typename T>
class CacheManager {
public:
    virtual void foreach(function<void(T&)> func) =0;
    virtual T get(string key) = 0;
    virtual void use(typename unordered_map<string,std::pair<T, std::list<string>::iterator>>::iterator& it) = 0;
    virtual void insert(string key, T obj) = 0;
    virtual string getHashName(T obj) = 0;
};

template<typename T>
class FileCacheManager : public CacheManager<T> {
private:
    int _capacity;
    unordered_map <string,std::pair<T, std::list<string>::iterator>> _cache;
    std::list <string> _lru;

public:
    virtual string getHashName(T obj) {

    }
    FileCacheManager(int capacity1){
        this->_capacity = capacity1;
    }

    void foreach(function<void(T&)> func) {
        for (string x : this->_lru) {
            func(this->_cache[x].first);
        }
    }
    T get(string key) {
        //if the key doesnt exsist
        auto item = this->_cache.find(key);
        ifstream data;
        if (item == this->_cache.end()) {
            T temp;
            //we need to check in the file exsist
            data.open(key, ios::in|ios::binary);
            if (!data.is_open()) {
                throw "Error";
            }
            data.read((char*) &temp, sizeof(temp));
            data.close();
            insert(key, temp);
            return temp;
        }
        use(item);
        return item->second.first;
    }
    void use(typename unordered_map<string,std::pair<T, std::list<string>::iterator>>::iterator& it) {
        this->_lru.erase(it->second.second);
        this->_lru.push_front(it->first);
        it->second.second = this->_lru.begin();
    }
    void insert(string key, T obj) {
        fstream data;
        auto item = this->_cache.find(key);
        if (item != this->_cache.end()) {
            use(item);
            this->_cache[key] = {obj, this->_lru.begin()};
        }
        else {
            if (this->_cache.size() == (unsigned )this->_capacity) {
                this->_cache.erase(this->_lru.back());
                this->_lru.pop_back();
            }
            this->_lru.push_front(key);
            this->_cache.insert({key, {obj,this->_lru.begin()} });
        }
        data.open(key, ios::out | ios::binary);
        if (!data.is_open()) {
            throw "Error";
        }
        data.write((char*)&obj, sizeof(obj));
        data.close();
    }

};

#endif //UNTITLED9_CACHEMANAGER_H
