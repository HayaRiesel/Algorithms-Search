

#include "Boot.h"
using namespace boot;
int main(int argc, char *argv[]) {
    int port;
    if(argv[1] != NULL){
        port = stod(argv[1]);
    }else{
        port = 5600;
    }
    Main m(port);
    m.main();
}