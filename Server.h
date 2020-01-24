//
// Created by yaellax on 16/01/2020.
//

#ifndef UNTITLED9_SERVER_H
#define UNTITLED9_SERVER_H

#include "ClientHandler.h"
namespace side_server {
    class Server {
        virtual void open(int port,ClientHandler&) = 0;
        virtual void stop() = 0;

    };

}


class MyParallelServer : public side_server::Server {
private:
    ClientHandler *c;
    int socketfd;
    vector<thread> threadVector;
    void getClient(int client_socket);

public:
    void stop();

    void open(int port, ClientHandler &c1);
};

class MySerialServer : public side_server::Server {
private:
    ClientHandler* c;
    int socketfd;
    void getClient(int socketfd, sockaddr_in address);

public:
    void stop();
    void open(int port,ClientHandler& c1);

};
#endif //UNTITLED9_SERVER_H
