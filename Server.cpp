//
// Created by yaellax on 16/01/2020.
//

#include "Server.h"
void MyParallelServer::getClient(int client_socket){
    ClientHandler *com = c->deepCopy();
    com->handleClient(client_socket);
    close(client_socket);
}
void MyParallelServer::stop() {
    close(socketfd); //closing the listening socket
}
void MyParallelServer::open(int port, ClientHandler &) {
    this->c = &c1;
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        //return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        //return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 10) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        // return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }


    while(true){
        struct timeval tv;
        tv.tv_sec = 120;
        tv.tv_usec = 0;
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

        int client_socket = accept(socketfd, (struct sockaddr *) &address,
                                   (socklen_t * ) &address);
        if (client_socket == -1) {
            std::cerr << "Timeout for connection is over" << std::endl;
            break;
            // return -4;
        } else {
            std::cerr << " accepting client" << std::endl;
        }
        threadVector.push_back(thread(&MyParallelServer::getClient,this, client_socket));
    }


    //close the threads
    for(int i=0;i<threadVector.size();i++){
        threadVector[i].join();
    }

    this->stop(); //closing the listening socket

}


void MySerialServer::getClient(int socketfd, sockaddr_in address) {
    while (1) {
        struct timeval tv;
        tv.tv_sec = 120;
        tv.tv_usec = 0;
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);


        int client_socket = accept(socketfd, (struct sockaddr *) &address,
                                   (socklen_t * ) &address);

        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
            break;
        }


        //reading from client
        c->handleClient(client_socket);
        close(client_socket);

    }
    this->stop();

}
void MySerialServer::stop() {
    close(socketfd); //closing the listening socket
}
void MySerialServer::open(int port, ClientHandler &) {
    this->c = &c1;
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        //return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        //return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        // return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    thread(&MySerialServer::getClient,this, socketfd, address).join();
    //close(socketfd); //closing the listening socket

}

