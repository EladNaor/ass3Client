

#ifndef ASS3CLIENT_KEYBOARDPROTOCOL_H
#define ASS3CLIENT_KEYBOARDPROTOCOL_H


#include "ConnectionHandler.h"

#include "MessageEncDec.h"

class KeyBoardProtocol {

public:
    ConnectionHandler* connectionHandler;
    KeyBoardProtocol(ConnectionHandler *pHandler);

    void operator()();

    void run();
};


#endif //ASS3CLIENT_KEYBOARDPROTOCOL_H
