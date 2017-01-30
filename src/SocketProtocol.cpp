#include <boost/thread.hpp>
#include <fstream>
#include "../include/SocketProtocol.h"
#include "../include/Packet.h"

string SocketProtocol::action = "resting";
bool SocketProtocol::stayConnected = true;
bool SocketProtocol::isReading = false;
string SocketProtocol::fileName = "";

queue<vector<char>> SocketProtocol::devidedDataBlocks = queue<vector<char>>();

void SocketProtocol::operator()() {
    stayConnected = true;
    run();
    boost::this_thread::yield();
}

void SocketProtocol::run() {

    while (stayConnected) {
        Packet* answer = nullptr;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler->getPacketFromSocket(&answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        } else {
            short opcode = answer->getOpCode();
            switch (opcode) {
                case 3: {
                    std::vector<char> data;
                    copy ( answer->getData()->begin(), answer->getData()->begin() + answer->getPacketSize(), std::back_inserter(data) );
                    devidedDataBlocks.push(data);
                    pack.createACKpacket(answer->getBlockNumber());
                    connectionHandler->sendPacketToSocket(&pack);
                    if (answer->getPacketSize() < 512) {
                        if (isReading) {
                            createFileFromQueue();
                            cout<< "RRQ " << fileName << " complete" << endl;
                        } else {
                            printDirq();
                        }
                    }
                    break;
                }
                case 4:{
                    cout<< "Ack " <<answer->getBlockNumber() << endl;
                    if(action.compare("disc")==0){
                        stayConnected = false;
                    } else if(!action.compare("logrq")==0) {
                        if(!devidedDataBlocks.empty()) {
                            data = devidedDataBlocks.front();
                            pack.createDATApacket((short) data.size(),(short) (answer->getBlockNumber() + 1), data);
                            connectionHandler->sendPacketToSocket(&pack);
                            devidedDataBlocks.pop();
                        }
                    }
                    break;
                }


                case 5: {
                    cout << "Error " << answer->getErrCode() << endl;
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
    string toPrint = "";
    while (!devidedDataBlocks.empty()) {
        vector<char> &vec = devidedDataBlocks.front();
        // std:: string cur(vec.begin(), vec.end());

        for (unsigned int i = 0; i < vec.size(); i++) {
            char curr = vec.at(i);
            if (curr == '\n') {
                cout << toPrint << endl;
                toPrint="";
            } else
                toPrint = toPrint + curr;

        }

        devidedDataBlocks.pop();

    }
}

void SocketProtocol::createFileFromQueue() {
    std::ofstream fileToWrite;
    fileToWrite.open(fileName, std::ios::out | ios::binary);

    if (fileToWrite.is_open()) {
        vector<char> block = turnQueueToChars();
        fileToWrite.write(block.data(), block.size());

        fileToWrite.close();
    }
    else
    {
        cout<< "Error 1"<< endl;
        Packet* err = new Packet();
        err->createERRORpacket(1, "");
        connectionHandler->sendPacketToSocket(err);
    }
}

vector<char> SocketProtocol::turnQueueToChars() {
    vector<char> blockFinal;
    vector<char> block;
    while (!(&devidedDataBlocks)->empty())
    {
        block = devidedDataBlocks.front();
        devidedDataBlocks.pop();
        blockFinal.insert(blockFinal.end(),block.begin(), block.end());
    }

    return blockFinal;
}

SocketProtocol::~SocketProtocol() {

}

SocketProtocol& SocketProtocol::operator=(const SocketProtocol &rhs) {
    data = rhs.data ;
           pack = rhs.pack ;
           isReading = rhs.isReading;
           connectionHandler = rhs.connectionHandler;

    return *this;
}

SocketProtocol::SocketProtocol(ConnectionHandler *connectionHandler) : data(), pack(),
                                                                       connectionHandler(connectionHandler) {}

SocketProtocol::SocketProtocol(const SocketProtocol& sp) : data(sp.data), pack(sp.pack),
                                                                       connectionHandler(sp.connectionHandler) {}
