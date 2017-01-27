

#ifndef ASS3CLIENT_SOCKETPROTOCOL_H
#define ASS3CLIENT_SOCKETPROTOCOL_H


#include <queue>
#include "ConnectionHandler.h"

class SocketProtocol {
private:
    vector<char> data;
    Packet pack;
    bool isReading;

public:
    static string action;
    static bool stayConnected;
    ConnectionHandler* connectionHandler;
    SocketProtocol(ConnectionHandler *pHandler);
    void operator()();
    void run();
    void printDirq();

    static queue<vector<char>> devidedDataBlocks;
};


#endif //ASS3CLIENT_SOCKETPROTOCOL_H
