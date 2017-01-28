#include <boost/thread/win32/thread_data.hpp>
#include <io.h>
#include <vector>
#include <bits/ios_base.h>
#include <ios>
#include <fstream>
#include "../include/SocketProtocol.h"
#include "../include/Packet.h"

string SocketProtocol::action = "resting";
bool SocketProtocol::stayConnected = true;
queue<vector<char>> SocketProtocol::devidedDataBlocks = queue<vector<char>>();

SocketProtocol::SocketProtocol(ConnectionHandler *pHandler):connectionHandler(pHandler)  {

}

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
                case 4:{
                    cout<< "Ack " <<answer->getBlockNumber() << endl;
                    if(action.compare("disc")==0){
                        stayConnected = false;
                    } else if(!action.compare("logrq")==0) {
                        if(!devidedDataBlocks.empty()) {
                            data = *(answer->getData());
                            pack.createDATApacket((short) answer->getBlockNumber() + 1, (short) data.size(), data);
                            connectionHandler->sendPacketToSocket(&pack);
                        }
                    }
                    break;0;
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
string toPrint="";
    while(!devidedDataBlocks.empty()){
        vector<char>& vec=devidedDataBlocks.front();
        devidedDataBlocks.pop();
        for(unsigned int i=0; i<vec.size(); i++)
            toPrint+=vec.at(i) + " ";
    }
    cout << toPrint << endl;
}

void SocketProtocol::createFileFromQueue() {
    std::ofstream fileToWrite("", std::ios::out | ios::binary);
    std::vector<char>* file;
    file = turnQueueToChars();
    fileToWrite.is_open();
    fileToWrite.write(file->data(), file->size());

    fileToWrite.close();
}

std::vector<char>* SocketProtocol::turnQueueToChars() {
    std::vector<char>* fileChars = &devidedDataBlocks.front();
    devidedDataBlocks.pop();
    int next = 0;
    while (!(&devidedDataBlocks)->empty()) {
        std::vector<char> *block = &devidedDataBlocks.front();
        devidedDataBlocks.pop();
        fileChars->insert(fileChars->end(),block->begin(),block->end());
    }

    return fileChars;
}