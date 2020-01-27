# HW4

Search algorithms, CPP language – HW4

Description
the purpose of this project is to run Search algorithms. By the Search algorithms the program finds the best way to go in a graph.

Program structure:
the program has 3 parts.
* server - the parts that open server that client can connect it and send their problem
* client handler - the part that read the data that receive from the server and analyze it.
* solver - the part that calculate the answer and return it to the client

Open server
We support 2 kind of server. A serial server that handle every time one client and a parallel server that can handle client in parallel.

Client handler
We support 2 kind of client handler. One that read the data and make it a string and another that read the data line by line and analyze it to matrix with entry and end points.

Solver
Every solver has his own purpose. All of them get the problem we receive from the client and solve it. Here we use the Search algorithms to return the best way to go in a graph. 
Installation
To use our program you need to write this command line on the terminal(Our program support Linux) and run this:
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
After that you need to open a client support TCP and connect to the server. The default port to use is 5600 but can accept another b the un command.

Support
for any questions you can talk with us in this Email
yaellax@gmail.com
hayaler88@gmail.com
Authors and acknowledgment
Haya Rizel and Yael Lax-Thee,  CS students from Bar-ILan university, Israel.
