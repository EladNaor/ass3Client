

#include <boost/thread/win32/thread_data.hpp>
#include "../include/KeyBoardProtocol.h"
#include "../include/Packet.h"
#include "../include/SocketProtocol.h"

using namespace std;


KeyBoardProtocol::KeyBoardProtocol(ConnectionHandler *pHandler) : connectionHandler(pHandler) {

}


KeyBoardProtocol::KeyBoardProtocol(const KeyBoardProtocol& aProtocol) : connectionHandler(aProtocol.connectionHandler) {

}


void KeyBoardProtocol::operator()() {
    run();
    boost::this_thread::yield();
}

void KeyBoardProtocol::run() {
    while (SocketProtocol::stayConnected) {
        const short bufsize = 512;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        string command = line.substr(0, line.find(' '));
        string extraData = command.length()!=line.length()? line.substr(command.length() + 1, line.length() - 1):"";
        Packet *p = nullptr;
        int commandType = command.compare("LOGRQ") ? command.compare("DELRQ") ? command.compare("RRQ") ?
                                                                                command.compare("WRQ")
                                                                                ? command.compare("DIRQ")
                                                                                  ? command.compare("DISC")
                                                                                    ?0:10:6:2:1:8:7;
        switch (commandType) {
            case 7 : {
                if (!extraData.empty())
                {
                    p=new Packet();
                    p->createLOGRQpacket(extraData);
                    SocketProtocol::action="logrq";
                } else{
                    std::cout << "Error 1" << endl;
                }
                break;
            }
            case 8 : {
                if (!extraData.empty())
                {
                    p=new Packet();
                    p->createDELRQpacket(extraData);
                } else{
                    std::cout << "Error 1" << endl;
                }

                break;
            }
            case 1  : {
                if (!extraData.empty())
                {
                    p=new Packet();
                    p->createRRQpacket(extraData);
                    SocketProtocol::isReading = true;
                    SocketProtocol::fileName=extraData;
                } else{
                    std::cout << "Error 1" << endl;
                }
                break;
            }
            case 2 : {
                if (!extraData.empty())
                {
                    p=new Packet();
                    p->createWRQpacket(extraData);
                } else{
                    std::cout << "Error 1" << endl;
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
                    SocketProtocol::action="disc";
                }
                break;
            }
            default:
                break;

        }
        if (p != nullptr) {

            if (!connectionHandler->sendPacketToSocket(p)) {
                cout << "Error 0" << endl;
            }
            else
            {
                //so the keyboard thread won't do the main while again
                // and get stuck waiting for input
                while (SocketProtocol::stayConnected && SocketProtocol::action.compare("disc")==0) {}
            }
        } else {
            cout << "Error 0" << endl;
        }
    }
}

KeyBoardProtocol::~KeyBoardProtocol() {

}

KeyBoardProtocol& KeyBoardProtocol::operator=(const KeyBoardProtocol &rhs)  {
     connectionHandler = rhs.connectionHandler;
    return *this;
}
