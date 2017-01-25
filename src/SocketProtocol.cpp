//
// Created by Orel Hazan on 25/01/2017.
//

#include <boost/thread/win32/thread_data.hpp>
#include "../include/SocketProtocol.h"

SocketProtocol::SocketProtocol(ConnectionHandler *pHandler):connectionHandler(pHandler)  {

}

void SocketProtocol::operator()() {
    run();
    boost::this_thread::yield();
}

void SocketProtocol::run() {
    std::string answer;

    while(1) {
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler->getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

        int len = answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        answer.resize(len - 1);
        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }

}
