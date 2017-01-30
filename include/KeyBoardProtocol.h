

#ifndef ASS3CLIENT_KEYBOARDPROTOCOL_H
#define ASS3CLIENT_KEYBOARDPROTOCOL_H


#include "ConnectionHandler.h"

#include "MessageEncDec.h"

class KeyBoardProtocol {

public:
    KeyBoardProtocol(const KeyBoardProtocol &aProtocol);

    KeyBoardProtocol& operator=(const KeyBoardProtocol &rhs) ;

    virtual ~KeyBoardProtocol();

    ConnectionHandler* connectionHandler;
    KeyBoardProtocol(ConnectionHandler *pHandler);

    void operator()();

    void run();

    void writeFileIntoQueue(string basic_string);
};


#endif //ASS3CLIENT_KEYBOARDPROTOCOL_H
