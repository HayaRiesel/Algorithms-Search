#include "Server.h"


//namespace boot {
    int main() {
        //MyParallelServer server1;
        MyParallelServer server1;
        //MyTestClientHandler ch;
        Solver<Matrix<double>,string>* s = new MatrixSolver<Matrix<double>,string>();
        ClientHandler* ch = new ClientHandlerMat(s);
        server1.open(5400, *ch);

        return 1;
    }
//};