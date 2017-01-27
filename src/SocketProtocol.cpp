#include <boost/thread/win32/thread_data.hpp>
#include <io.h>
#include <vector>
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
        }
        else{
            short opcode = answer->getOpCode();
            switch (opcode) {
                case 3: {
                    pack.createACKpacket(answer->getBlockNumber());
                    devidedDataBlocks.push(*answer->getData());
                    if (answer->getData()->size() < 512) {
                        if (isReading) {
                            //read();
                        } else {
                            printDirq();
                        }
                    }
                    break;
                }


                case 5: {
                    cout << "Error " + answer->getErrCode() << endl;
                    break;
                }

                case 9:{
                    string adOrDel="";
                    if(answer->getAddedOrDeleted())
                        adOrDel+="add";
                    else
                        adOrDel+="del";
                    cout << "BCAST " +adOrDel +" " + answer->getString() << endl;
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
