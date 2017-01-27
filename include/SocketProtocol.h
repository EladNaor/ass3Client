

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

    static queue<vector<char>> devidedDataBlocks;
    static string action;
    static bool stayConnected;
    ConnectionHandler* connectionHandler;
    SocketProtocol(ConnectionHandler *pHandler);
    void operator()();
    void run();
    void printDirq();

    vector<char>* turnQueueToChars();

    void createFileFromQueue();
};


#endif //ASS3CLIENT_SOCKETPROTOCOL_H
