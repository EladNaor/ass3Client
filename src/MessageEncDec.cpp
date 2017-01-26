//#include "../include/MessageEncDec.h"

#include <string>
#include <vector>
#include "../include/Packet.h"

using namespace std;
class MessageEncDec {

private:
    Packet *p = nullptr;
    short opCode = 0;
    vector<char>* charOfOpCode;
    int i = 0;
    vector<char>* charBuffer;

    //For DATA Packets:
    int j = 0;
    int counter = 0;
    short packetSize = 0;
    short blockNumber = 0;
    vector<char> *charsOfDataPacketSize;
    vector<char> *charsOfBlockNumber;
    vector<char> *data = new vector<char>();

    //for ERROR Packets
    int k = 0;
    short errCode = 0;
    vector<char> *charsOfErrorCode;

    //For Encoder
    vector<char> ans;

    //For BCAST Packet
    bool delOrAdd = false;


public:
    virtual ~MessageEncDec() {
        delete p;
        delete charBuffer;
        delete data;
    }


    virtual void errorInit();

    virtual void init();

    virtual void dataInit();

    virtual Packet *decodeNextByte(char nextByte);

    virtual std::vector<char> encode(Packet *message);

    short bytesToShort(char *bytesArr);

    void shortToBytes(short num, char *bytesArr);

private:
    string charBufferToString(vector<char> *charBuffer);

    char* vecToArr(vector<char>& vector1);

    vector<char> arrToVec(char* c);
};

void MessageEncDec::init() {
    p = nullptr;
    i = 0;
    delOrAdd = false;
    charOfOpCode = new vector<char>;
    charBuffer = new vector<char>;
}

void MessageEncDec::errorInit() {
    k = 0;
    counter = 0;
    charsOfErrorCode = new vector<char>(2);
}

void MessageEncDec::dataInit() {
    j = 0;
    counter = 0;
    charsOfDataPacketSize = new vector<char>(2);
    charsOfBlockNumber = new vector<char>(2);
    data = new vector<char>();
}

char* MessageEncDec::vecToArr(vector<char>& v){
    // Get a char pointer to the data in the vector
    char* buf = &v[0];
    return buf;
}

vector<char> MessageEncDec::arrToVec(char* c){
    int size=sizeof(c);
    vector<char> v (c, c+size);
    return v;
}

Packet* MessageEncDec::decodeNextByte(char nextByte) {
    if (opCode == 0) {
        charOfOpCode->assign(i,nextByte);
        i++;
        if (i == 2) {
            opCode = bytesToShort(vecToArr(*charOfOpCode));
            init();
        }
        return nullptr;
    }

    switch (opCode) {
        case 3: {
            if (j < 4) {
                if (j == 0 || j == 1) {
                    charsOfDataPacketSize->assign(j,nextByte);
                    j++;
                    return nullptr;
                }
                if (j == 2 || j == 3) {
                    charsOfBlockNumber->assign(j-2,nextByte);
                    if (j == 3) {
                        packetSize = bytesToShort(vecToArr(*charsOfDataPacketSize));
                        blockNumber = bytesToShort(vecToArr(*charsOfBlockNumber));
                    }
                    j++;
                    return nullptr;
                }
            } else {
                if (counter <= packetSize) {
                    data->assign(counter,nextByte);
                    counter++;

                    if (counter == packetSize) {
                        p = new Packet();
                        p->createDATApacket(packetSize, blockNumber, *data);
                        dataInit();
                        opCode = 0;
                        return p;
                    }
                    return nullptr;
                }
            }
        }

        case 4: {
            if (k == 0 || k == 1) {
                charsOfBlockNumber->assign(k,nextByte);
                k++;
                if (k == 2) {
                    blockNumber = bytesToShort(vecToArr(*charsOfBlockNumber));
                    p = new Packet();
                    p->createACKpacket(blockNumber);
                    opCode = 0;
                    errorInit();
                    return p;
                }
                return nullptr;
            }
        }

        case 5: {
            if (k < 2) {
                charsOfErrorCode->assign(k,nextByte) ;
                k++;
                return nullptr;
            }
            if (k == 2) {
                errCode = bytesToShort(vecToArr(*charsOfErrorCode));
                k++;
            }
            if (nextByte != 0) {
                charBuffer->assign(counter,nextByte);
                counter++;
                return nullptr;
            } else {
                string errMsg = charBufferToString(charBuffer);
                p = new Packet();
                p->createERRORpacket(errCode, errMsg);
                opCode = 0;
                errorInit();
                return p;
            }
        }

        case 9: {
            if (j == 0 && nextByte == 1) {
                delOrAdd = true;
                j++;
                return nullptr;
            }
            if (nextByte != 0) {
                charBuffer->assign(j-1,nextByte);
                j++;
                return nullptr;
            } else {
                string fileName = charBufferToString(charBuffer);
                p = new Packet();
                p->createBCASTpacket(delOrAdd, fileName);
                opCode = 0;
                j = 0;
                return p;
            }
        }
    }
    return nullptr;
}


//std::vector<char> MessageEncDec::encode(Packet *message) {
//    std::vector<char> opCodeBytes = shortToBytes(message->getOpCode());
//    switch (message->getOpCode()) {
//        case 1:
//        case 2:
//        case 7:
//        case 8: {
////            ans = std::vector<char>(message->getString().getBytes()->length + 3);
//            ans[0] = opCodeBytes[0];
//            ans[1] = opCodeBytes[1];
//            ans[ans.size() - 1] = 0;
////            std::vector<char> string = message->getString().getBytes();
//            for (int i = 2; i < string.size() + 2; i++) {
//                ans[i] = string[i - 2];
//            }
//            break;
//        }
//
//        case 3: {
//            ans = std::vector<char>(message->getPacketSize() + 6);
//            ans[0] = opCodeBytes[0];
//            ans[1] = opCodeBytes[1];
//            std::vector<char> temp = shortToBytes(message->getPacketSize());
//            ans[2] = temp[0];
//            ans[3] = temp[1];
//            temp = shortToBytes(message->getBlockNumber());
//            ans[4] = temp[0];
//            ans[5] = temp[1];
//            temp = message->getData();
//            for (int i = 6; i < temp.size() + 6; i++) {
//                ans[i] = temp[i - 6];
//            }
//            break;
//        }
//
//        case 4: {
//            ans = std::vector<char>(4);
//            ans[0] = opCodeBytes[0];
//            ans[1] = opCodeBytes[1];
//    //        std::vector<char> temp = shortToBytes(message->getBlockNumber());
//            ans[2] = temp[0];
//            ans[3] = temp[1];
//            break;
//        }
//
//        case 5: {
////            ans = std::vector<char>(message->getString().getBytes()->length + 5);
//            ans[0] = opCodeBytes[0];
//            ans[1] = opCodeBytes[1];
//            ans[ans.size() - 1] = 0;
//  //          std::vector<char> temp = shortToBytes(message->getErrCode());
//            ans[2] = temp[0];
//            ans[3] = temp[1];
////            std::vector<char> string = message->getString().getBytes();
//            for (int i = 4; i < string.size() + 4; i++) {
//   //             ans[i] = string[i - 4];
//            }
//            break;
//        }
//
//        case 6:
//        case 10: {
//            ans = opCodeBytes;
//            break;
//        }
//
//        case 9: {
////            ans = std::vector<char>(message->getString().getBytes()->length + 4);
//            ans[0] = opCodeBytes[0];
//            ans[1] = opCodeBytes[1];
//            ans[ans.size() - 1] = 0;
//            if (message->getAddedOrDeleted()) {
//                ans[2] = 1;
//            } else {
//                ans[2] = 0;
//            }
////            std::vector<char> string = message->getString().getBytes();
//            for (int i = 3; i < string.size() + 3; i++) {
//    //            ans[i] = string[i - 3];
//            }
//            break;
//        }
//    }
//    return ans;
}


short MessageEncDec::bytesToShort(char* bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

void MessageEncDec::shortToBytes(short num, char* bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

string MessageEncDec::charBufferToString(vector<char> *charBuffer) {
    charBuffer->shrink_to_fit();
    string ans = "";
    for (int i = 0; i < charBuffer->size(); i++) {
        ans = ans + charBuffer->at(i);
    }
    return ans;
}


