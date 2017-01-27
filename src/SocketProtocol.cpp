#include <boost/thread/win32/thread_data.hpp>
#include <io.h>
#include <vector>
#include "../include/SocketProtocol.h"
#include "../include/Packet.h"

string SocketProtocol::action = "resting";
bool SocketProtocol::stayConnected = true;
SocketProtocol::SocketProtocol(ConnectionHandler *pHandler):connectionHandler(pHandler)  {

}

void SocketProtocol::operator()() {
    stayConnected = true;
    run();
    boost::this_thread::yield();
}

void SocketProtocol::run() {
    Packet *answer = nullptr;

    while (stayConnected) {
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler->getPacketFromSocket(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        } else {
            short opcode = answer->getOpCode();
            switch (opcode) {
                case 3: {
                    pack.createACKpacket(answer->getBlockNumber());
                    devidedDataBlocks.push(*answer->getData());
                    if (answer->getData()->size() < 512) {
                        if (isReading) {
                            //createFileFromQueue();
                        } else {
                            printDirq();
                        }
                    }
                    break;
                }
                case 4:
                    if (action.compare("disc")) {
                        stayConnected = false;
                    } else if (!action.compare("logrq")) {
                        if (!devidedDataBlocks.empty()) {
                            data = *(answer->getData());
                            pack.createDATApacket((short) answer->getBlockNumber() + 1, (short) data.size(), data);
                            connectionHandler->sendPacketToSocket(&pack);
                        }
                    }
                    break;

                case 5: {
                    cout << "Error " + answer->getErrCode() << endl;
                    break;
                }

                case 9: {
                    string adOrDel = "";
                    if (answer->getAddedOrDeleted())
                        adOrDel += "add";
                    else
                        adOrDel += "del";
                    cout << "BCAST " + adOrDel + " " + answer->getString() << endl;
                }
            }
        }
    }
}

void SocketProtocol::printDirq() {
string toPrint="";
    for_each(auto vector<char> vec : devidedDataBlocks){
        for(unsigned int i=0; i<vec.size(); i++)
            toPrint+=vec.at(i) + " ";
    }
    cout << toPrint << endl;
}
/*

void SocketProtocol::createFileFromQueue() {
    std::vector<char> chars = this->turnQueueToChars();
    Path *path = Paths->get(L"./Files/",this->fileName);
    try
    {
        Files::write(path, bytes);
    }
    catch (const IOException &e)
    {
        Packet *pack = new Packet();
        pack->createERRORpacket(static_cast<short>(1), L"couldn't write to disc");
        connections->send(connectionId, pack);
        e->printStackTrace();
    }
    this->reset();
}

std::vector<char> SocketProtocol::turnQueueToChars() {
    std::vector<char> fileChars = devidedDataBlocks.back();
    int next = 0;
    while (!devidedDataQueue->isEmpty()) {

    }
    return fileChars;
}