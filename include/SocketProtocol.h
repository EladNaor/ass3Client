//
// Created by Orel Hazan on 25/01/2017.
//

#ifndef ASS3CLIENT_SOCKETPROTOCOL_H
#define ASS3CLIENT_SOCKETPROTOCOL_H


#include "ConnectionHandler.h"

class SocketProtocol {
public:

    ConnectionHandler* connectionHandler;
    SocketProtocol(ConnectionHandler *pHandler);

    void operator()();

    void run();
};


#endif //ASS3CLIENT_SOCKETPROTOCOL_H
