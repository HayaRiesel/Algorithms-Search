//
// Created by yaellax on 12/01/2020.
//

#ifndef UNTITLED9_CLIENTHANDLER_H
#define UNTITLED9_CLIENTHANDLER_H
#include <sys/socket.h>
//#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <fstream>
#include "Solver.h"
#include <cstring>
#include <thread>
#include <hash_map>
#include "CacheManager.h"
#include <mutex>


using namespace std;

class ClientHandler {
public:
    virtual void handleClient (int client_socket) = 0;
    virtual ClientHandler* deepCopy() =0;
};

class MyTestClientHandler : public ClientHandler{
private:
    Solver<string ,string>* solver;
    CacheManager<string>* cacheManager;

public:
    MyTestClientHandler();
    MyTestClientHandler(CacheManager<string> *cache);

    ClientHandler* deepCopy();
    void handleClient (int client_socket);
};


class ClientHandlerMat : public ClientHandler{
private:
    Solver<Matrix<double>,string>* solver;
    CacheManager<string>* cacheManager;
    void setTheLine(vector<vector<double>> theMatrix,char* buffer, char* halfBuf);
    vector<double> makeRow(string line);

public:
    ClientHandlerMat();
    ClientHandlerMat(Solver<Matrix<double>,string>* s);
    ClientHandlerMat(CacheManager<string> *cache);

    ClientHandler* deepCopy();

    void handleClient (int client_socket);

#endif //UNTITLED9_CLIENTHANDLER_H
