//
// Created by hayal on 24/01/2020.
//

#ifndef UNTITLED9_BOOT_H
#define UNTITLED9_BOOT_H
#include "Server.h"


namespace boot {
    class Main;
}

class boot :: Main{
private:
    int port;
public:
    Main(int port);
    int main();
};

#endif //UNTITLED9_BOOT_H
