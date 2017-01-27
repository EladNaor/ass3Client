#include <boost/thread.hpp>
#include "../include/KeyBoardProtocol.h"
#include "../include/SocketProtocol.h"

int main(int argc, char *argv[]){
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }

    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler* connectionHandler = new ConnectionHandler(host, port);
    if (!connectionHandler->connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }


    SocketProtocol task2 = SocketProtocol(connectionHandler);
    KeyBoardProtocol task1 = KeyBoardProtocol(connectionHandler);

    boost::thread th1(task1);
    boost::thread th2(task2);
    th1.join();
    th2.join();

    return 0;
}