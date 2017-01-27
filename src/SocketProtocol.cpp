//
// Created by Orel Hazan on 25/01/2017.
//

#include <boost/thread/win32/thread_data.hpp>
#include "../include/SocketProtocol.h"
#include "../include/Packet.h"

SocketProtocol::SocketProtocol(ConnectionHandler *pHandler):connectionHandler(pHandler)  {

}

void SocketProtocol::operator()() {
    run();
    boost::this_thread::yield();
}

void SocketProtocol::run() {
    Packet* answer = nullptr;

    while(1) {
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler->getPacketFromSocket(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        } else
        {

        }
    }

}
