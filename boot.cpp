//
// Created by hayal on 24/01/2020.
//

#include "boot.h"
boot::Main::Main(int port1) {
    this->port = port1;
}

int boot::Main::main() {
    MyParallelServer server1;
    Solver<Matrix<double>,string>* s = new MatrixSolver();
    ClientHandler* ch = new ClientHandlerMat(s);
    server1.open(this->port, *ch);

    delete(s);
    delete(ch);
    return 1;

}