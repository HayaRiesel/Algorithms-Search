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
    MyTestClientHandler(){
        this->cacheManager = new FileCacheManager<string>(1);
        this->solver = new StringReverser<string,string>();
    }
    MyTestClientHandler(CacheManager<string> *cache){
        this->cacheManager = cache;
        this->solver = new StringReverser<string,string>();
    }

    ClientHandler* deepCopy(){
        return new MyTestClientHandler(this->cacheManager);
    }


    void handleClient (int client_socket) {
        while (1) {
            char buffer[1024] = {0};
            read(client_socket, buffer, 1024);
            if (!strncmp(buffer, "end", 3)) {
                return;
            }
                std::cout << buffer << std::endl;
                string temp = buffer;
                temp = temp.substr(0, temp.size() - 2);
                //להוריד את \n
                string solution;
                try {
                    solution = cacheManager->get(temp);
                }
                catch (const char *msg) {
                    solution = solver->solveTheProb(temp);
                    cacheManager->insert(temp, solution);
                }
                std::cout << solution << std::endl;


                //writing back to client
                solution = solution + '\n';
                char *hello = new char[solution.length() + 1];
                strcpy(hello, solution.c_str());
                //send(client_socket,outputStream);
                send(client_socket, hello, strlen(hello), 0);
                //std::cout << "Hello message sent\n" << std::endl;
            }

        }
};


class ClientHandlerMat : public ClientHandler{
private:
    Solver<Matrix<double>,string>* solver;
    CacheManager<string>* cacheManager;

public:
    ClientHandlerMat(){
        this->cacheManager = new FileCacheManager<string>(5);
        this->solver = new MatrixSolver<Matrix<double>,string>();
    }
    ClientHandlerMat(Solver<Matrix<double>,string>* s){
        this->cacheManager = new FileCacheManager<string>(5);
        this->solver = s;
    }
    ClientHandlerMat(CacheManager<string> *cache){
        this->cacheManager = cache;
        this->solver = new MatrixSolver<Matrix<double>,string>();
    }

    ClientHandler* deepCopy(){
        this->solver->deepCopy();
        return new ClientHandlerMat(this->cacheManager);
    }
    void setTheLine(vector<vector<double>> theMatrix,char* buffer,string halfBuf) {
        string temp;
        if (halfBuf != "") {
            temp = halfBuf + buffer;
            halfBuf = "";
        } else {
            temp = buffer;
        }
        while (!temp.empty()) {
            int i = temp.find('\n');
            //didnt find the \n, hold the line
            if (i == -1) {
                halfBuf = temp;
                return;
            }
            string part = temp.substr(0,i);
            theMatrix.push_back(makeRow(part));
            temp = temp.substr(i + 1, temp.size());
        }
    }


    vector<double> makeRow(string line) {
        //find the num
        vector<double> lineMatrix;
        string num;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                lineMatrix.push_back(stod(num));
                num = "";
            } else {
                if (line[i] != ' ') {
                    num += line[i];
                }
            }
        }
            if (num != "") {
                lineMatrix.push_back(stod(num));
            }
        return lineMatrix;

    }
    void handleClient (int client_socket) {
        int numOfLine = 0;
        vector<vector<double>> theMatrix;
        string matString = "";
        string beginMat;
        string goalMat;
        string halfBuffer;
        while(1){
            char buffer[1024] = {0};
            read(client_socket, buffer, 1024);
            string temp = buffer;
            numOfLine++;
            temp = temp.substr(0, temp.size() - 2);
            beginMat = goalMat;
            goalMat = temp;
            setTheLine(theMatrix,buffer,halfBuffer);
            if (!strncmp(buffer, "end", 3)) {
                theMatrix.pop_back();
                theMatrix.pop_back();
                break;
            }

                //theMatrix.push_back(makeRow(temp));
                //temp.erase(remove(temp.begin(), temp.end(), " "),temp.end());
                matString+= temp;
            }
        int indexBeginX = stoi(string() +beginMat[0]);
        int indexBeginY = stoi(string() +beginMat[2]);
        int indexGoalX = stoi(string() +goalMat[0]);
        int indexGoalY = stoi(string() +goalMat[2]);

        Matrix<double>* matrix = new Matrix<double>(theMatrix,{indexBeginX,indexBeginY},{indexGoalX,indexGoalY});
            //std::cout << buffer << std::endl;
            //hash table
            size_t hashName = hash<string>{}(matString) ;
            string matKey = to_string((hashName));
            string solution;
            try {
                //get get string
                solution = cacheManager->get(matKey);
            }
             catch (const char *msg) {
                 solution = solver->solveTheProb(*matrix);
                cacheManager->insert(matKey, solution);
            }
            std::cout << solution << std::endl;


            //writing back to client

            string answerToServer;
            answerToServer = solution + '\n';
            char *hello = new char[answerToServer.length() + 1];
            strcpy(hello, answerToServer.c_str());
            //send(client_socket,outputStream);
            send(client_socket, hello, strlen(hello), 0);
            std::cout << "Hello message sent\n" << std::endl;
        }
};

#endif //UNTITLED9_CLIENTHANDLER_H
