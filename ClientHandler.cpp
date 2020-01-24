//
// Created by yaellax on 12/01/2020.
//

#include "ClientHandler.h"

MyTestClientHandler::MyTestClientHandler() {
    this->cacheManager = new FileCacheManager<string>(1);
    this->solver = new StringReverser<string,string>();
}
MyTestClientHandler::MyTestClientHandler(CacheManager<string> *cache) {
    this->cacheManager = cache;
    this->solver = new StringReverser<string,string>();
}
ClientHandler* MyTestClientHandler::deepCopy() {
    return new MyTestClientHandler(this->cacheManager);
}
void MyTestClientHandler::handleClient(int client_socket) {
    while (1) {
        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);
        if (!strncmp(buffer, "end", 3)) {
            return;
        }
        std::cout << buffer << std::endl;
        string temp = buffer;
        temp = temp.substr(0, temp.size() - 2);
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
    }
}


ClientHandlerMat::ClientHandlerMat() {
    this->cacheManager = new FileCacheManager<string>(5);
    this->solver = new MatrixSolver<Matrix<double>,string>();
}
ClientHandlerMat::ClientHandlerMat(Solver<Matrix<double>, string> *s) {
    this->cacheManager = new FileCacheManager<string>(5);
    this->solver = s;
}
ClientHandlerMat::ClientHandlerMat(CacheManager<string> *cache) {
    this->cacheManager = cache;
    this->solver = new MatrixSolver<Matrix<double>,string>();
}
ClientHandler* ClientHandlerMat::deepCopy() {
    this->solver->deepCopy();
    return new ClientHandlerMat(this->cacheManager);
}
void ClientHandlerMat::setTheLine(vector<vector<double>> theMatrix,char* buffer, char* halfBuf){
    string temp;
    if (*halfBuf != "") {
        temp = *halfBuf + buffer;
    } else {
        temp = buffer;
    }

    while (!temp.empty()) {
        int i = temp.find('\n');
        //didnt find the \n, hold the line
        if (i == -1) {
            *halfBuf = temp[0];
            return;
        }
        string part = temp.substr(0,i);
        theMatrix.push_back(makeRow(part));
        temp = temp.substr(i + 1, temp.size());
    }

}
vector<double> ClientHandlerMat::makeRow(string line) {
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
void ClientHandlerMat::handleClient(int client_socket) {
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
        setTheLine(theMatrix,buffer, &halfBuffer);
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
        string s(cacheManager->get(matKey))
        solution = s;
    }
    catch (const char *msg) {
        solution = solver->solveTheProb(*matrix);
        char solutionInChar[solution.size() + 1];
        strcpy(solutionInChar, solution.c_str());	// or pass &s[0]

        cacheManager->insert(matKey, solutionInChar);
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