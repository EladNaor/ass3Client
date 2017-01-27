//
// Created by Orel Hazan on 25/01/2017.
//

#include <boost/thread/win32/thread_data.hpp>
#include "../include/KeyBoardProtocol.h"
#include "../include/Packet.h"

using namespace std;

KeyBoardProtocol::KeyBoardProtocol(ConnectionHandler *pHandler) : connectionHandler(pHandler) {

}

void KeyBoardProtocol::operator()() {
    run();
    boost::this_thread::yield();
}

void KeyBoardProtocol::run() {
    while (1) {
        const short bufsize = 512;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        string command = line.substr(0, line.find(' '));
        string extraData = line.substr(command.length() + 1, line.length() - 1);
        Packet* p = nullptr;
        int commandType = command.compare("LOGRQ") ? command.compare("DELRQ") ? command.compare("RRQ") ?
                                                                                  command.compare("WRQ")
                                                                                  ? command.compare("DIRQ")
                                                                                    ? command.compare("DISC")
                                                                                      ? 7 : 8 : 1 : 2 : 6 : 10 : 0;

        switch (commandType) {
            case 7 : {
                if (!extraData.empty())
                {
                    p=new Packet();
                    p->createLOGRQpacket(extraData);
                }
                break;
            }
            case 8 : {
                if (!extraData.empty())
                {
                    p=new Packet();
                    p->createDELRQpacket(extraData);
                }
                break;
            }
            case 1  : {
                if (!extraData.empty())
                {
                    p=new Packet();
                    p->createRRQpacket(extraData);
                }
                break;
            }
            case 2 : {
                if (!extraData.empty())
                {
                    p=new Packet();
                    p->createWRQpacket(extraData);
                }
                break;
            }
            case 6 : {
                if (extraData.empty())
                {
                    p=new Packet();
                    p->createDIRQpacket();
                }
                break;
            }
            case 10: {
                if (extraData.empty())
                {
                    p=new Packet();
                    p->createDISCpacket();
                }
                break;
            }
            default:
                break;

        }
        if (p!= nullptr) {
            vector<char> *encoded = encDec->encode(p);

            if (!connectionHandler->sendBytes(&encoded->at(0), encoded->size())) {
                //ERROR
                break;
            }
        }
    }
}