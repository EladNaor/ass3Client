//
// Created by Orel Hazan on 25/01/2017.
//

#include <boost/thread/win32/thread_data.hpp>
#include "../include/KeyBoardProtocol.h"

KeyBoardProtocol::KeyBoardProtocol(ConnectionHandler *pHandler) : connectionHandler(pHandler) {

}

void KeyBoardProtocol::operator()() {
    run();
    boost::this_thread::yield();
}

void KeyBoardProtocol::run() {
    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len = line.length();
        if (!connectionHandler->sendLine(line)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;

    }
}