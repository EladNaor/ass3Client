//
// Created by Orel Hazan on 25/01/2017.
//

#ifndef ASS3CLIENT_KEYBOARDPROTOCOL_H
#define ASS3CLIENT_KEYBOARDPROTOCOL_H


#include "ConnectionHandler.h"

#include "MessageEncDec.h"

class KeyBoardProtocol {

public:
    ConnectionHandler* connectionHandler;
    KeyBoardProtocol(ConnectionHandler *pHandler);
    MessageEncDec* encDec = new MessageEncDec();

    void operator()();

    void run();
};


#endif //ASS3CLIENT_KEYBOARDPROTOCOL_H
