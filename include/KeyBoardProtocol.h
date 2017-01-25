//
// Created by Orel Hazan on 25/01/2017.
//

#ifndef ASS3CLIENT_KEYBOARDPROTOCOL_H
#define ASS3CLIENT_KEYBOARDPROTOCOL_H


#include "ConnectionHandler.h"

class KeyBoardProtocol {

public:
    ConnectionHandler* connectionHandler;
    KeyBoardProtocol(ConnectionHandler *pHandler);

    void operator()();

    void run();
};


#endif //ASS3CLIENT_KEYBOARDPROTOCOL_H
