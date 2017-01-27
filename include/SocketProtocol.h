

#ifndef ASS3CLIENT_SOCKETPROTOCOL_H
#define ASS3CLIENT_SOCKETPROTOCOL_H


#include <queue>
#include "ConnectionHandler.h"

class SocketProtocol {
private:
    string action;
    queue<vector<char>> devidedDataBlocks;
    vector<char> data;
    Packet pack;
    bool isReading;
public:

    ConnectionHandler* connectionHandler;
    SocketProtocol(ConnectionHandler *pHandler);

    void operator()();

    void run();

    void printDirq();
};


#endif //ASS3CLIENT_SOCKETPROTOCOL_H
