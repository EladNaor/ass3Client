#include "../include/MessageEncDec.h"

using namespace std;

void MessageEncDec::init() {
    p = nullptr;
    i = 0;
    delOrAdd = false;
    charOfOpCode = new vector<char>(2);
    charBuffer = new vector<char>(512);
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
    data = new vector<char>(512);
}

char *MessageEncDec::vecToArr(vector<char> &v) {
    // Get a char pointer to the data in the vector
    char *buf = &v[0];
    return buf;
}

vector<char> MessageEncDec::arrToVec(char *c) {
    int size = sizeof(c);
    vector<char> v(c, c + size);
    return v;
}

Packet *MessageEncDec::decodeNextByte(char nextByte) {
    if (opCode == 0) {
        if (nextByte == 0)
            charOfOpCode = new vector<char>(2);
        charOfOpCode->at(i) = nextByte;
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
                    charsOfDataPacketSize->at(j) = nextByte;
                    j++;
                    return nullptr;
                }
                if (j == 2 || j == 3) {
                    charsOfBlockNumber->at(j - 2) = nextByte;
                    if (j == 3) {
                        packetSize = bytesToShort(vecToArr(*charsOfDataPacketSize));
                        blockNumber = bytesToShort(vecToArr(*charsOfBlockNumber));
                    }
                    j++;
                    return nullptr;
                }
            } else {
                if ((short) counter <= packetSize) {
                    data->at(counter) = nextByte;
                    counter++;
                    if ((short) counter == packetSize) {
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
                charsOfBlockNumber->at(k) = nextByte;
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
                charsOfErrorCode->at(k) = nextByte;
                k++;
                return nullptr;
            }
            if (k == 2) {
                errCode = bytesToShort(vecToArr(*charsOfErrorCode));
                k++;
            }
            if (nextByte != 0) {
                charBuffer->at(counter) = nextByte;
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
                charBuffer->at(j - 1) = nextByte;
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


vector<char> *MessageEncDec::encode(Packet *message) {
    vector<char> *opCodeBytes = new vector<char>[2];
    shortToBytes(message->getOpCode(), opCodeBytes);
    switch (message->getOpCode()) {
        case 1:
        case 2:
        case 7:
        case 8: {
            ans = new vector<char>(message->getString().size() + 3);
            ans->at(0) = opCodeBytes->at(0);
            ans->at(1) = opCodeBytes->at(1);
            ans->at(ans->size() - 1) = 0;
            string msgString = message->getString();
            for (unsigned int i = 2; i < msgString.size() + 2; i++) {
                ans->at(i) = msgString.at(i - 2);
            }
            break;
        }

        case 3: {
            ans = new vector<char>(message->getPacketSize() + 6);
            ans->at(0) = opCodeBytes->at(0);
            ans->at(1) = opCodeBytes->at(1);
            vector<char> *temp = new vector<char>();
            shortToBytes(message->getPacketSize(), temp);
            ans->at(2) = temp->at(0);
            ans->at(3) = temp->at(1);
            shortToBytes(message->getBlockNumber(), temp);
            ans->at(4) = temp->at(0);
            ans->at(5) = temp->at(1);
            temp = message->getData();
            for (unsigned int i = 6; i < temp->size() + 6; i++) {
                ans->at(i) = temp->at(i - 6);
            }
            break;
        }

        case 4: {
            ans = new vector<char>(4);
            ans->at(0) = opCodeBytes->at(0);
            ans->at(1) = opCodeBytes->at(1);
            vector<char> *temp = new vector<char>(2);
            shortToBytes(message->getBlockNumber(), temp);
            ans->at(2) = temp->at(0);
            ans->at(3) = temp->at(1);
            break;
        }

        case 5: {
            ans = new vector<char>(message->getString().size() + 5);
            ans->at(0) = opCodeBytes->at(0);
            ans->at(1) = opCodeBytes->at(1);
            ans->at(ans->size() - 1) = 0;
            vector<char> *temp = new vector<char>(2);
            shortToBytes(message->getErrCode(), temp);
            ans->at(2) = temp->at(0);
            ans->at(3) = temp->at(1);
            string msgString = message->getString();
            for (unsigned int i = 4; i < msgString.size() + 4; i++) {
                ans->at(i) = msgString.at(i - 4);
            }
            break;
        }

        case 6:
        case 10: {
            ans = new vector<char>();
            ans = opCodeBytes;
            break;
        }
    }
    return ans;
}


short MessageEncDec::bytesToShort(char *bytesArr) {
    short result = (short) ((bytesArr[0] & 0xff) << 8);
    result += (short) (bytesArr[1] & 0xff);
    return result;
}

void MessageEncDec::shortToBytes(short num, vector<char> *bytesArr) {
    bytesArr->insert(bytesArr->begin(), ((num >> 8) & 0xFF));
    bytesArr->insert(bytesArr->begin() + 1, (num & 0xFF));
}

string MessageEncDec::charBufferToString(vector<char> *charBuffer) {
    string ans = charBuffer->data();
//    for (unsigned int i = 0; i < charBuffer->size(); i++) {
//        ans = ans + charBuffer->at(i);
//    }
    return ans;
}

MessageEncDec::~MessageEncDec() {
    delete p;
    delete charBuffer;
    delete data;
}

MessageEncDec::MessageEncDec() : p(), opCode(), charOfOpCode(), i(),
                                 charBuffer(), j(), counter(),
                                 packetSize(), blockNumber(),
                                 charsOfDataPacketSize(),
                                 charsOfBlockNumber(), data(),
                                 k(), errCode(),
                                 charsOfErrorCode(), ans(),
                                 delOrAdd() {


    errorInit();

    init();

    dataInit();
}


MessageEncDec::MessageEncDec(const MessageEncDec& encDec) : p(encDec.p), opCode(encDec.opCode), charOfOpCode(encDec.charOfOpCode), i(encDec.i),
                                 charBuffer(encDec.charBuffer), j(encDec.j), counter(encDec.counter),
                                 packetSize(encDec.packetSize), blockNumber(encDec.blockNumber),
                                 charsOfDataPacketSize(encDec.charsOfDataPacketSize),
                                 charsOfBlockNumber(encDec.charsOfBlockNumber), data(encDec.data),
                                 k(encDec.k), errCode(encDec.errCode),
                                 charsOfErrorCode(encDec.charsOfErrorCode), ans(encDec.ans),
                                 delOrAdd(encDec.delOrAdd) {}



MessageEncDec& MessageEncDec::operator=(const MessageEncDec &rhs) {
    p = rhs.p;
    opCode = rhs.opCode;
    charOfOpCode = rhs.charOfOpCode;
    i = rhs.i;
    charBuffer = rhs.charBuffer;
    j = rhs.j;
    counter = rhs.counter;
    packetSize = rhs.packetSize;
    blockNumber = rhs.blockNumber;
    charsOfDataPacketSize = rhs.charsOfDataPacketSize;
    charsOfBlockNumber = rhs.charsOfBlockNumber;
    data = rhs.data;
    k = rhs.k;
    errCode = rhs.errCode;
    charsOfErrorCode = rhs.charsOfErrorCode;
    ans = rhs.ans;
    delOrAdd = rhs.delOrAdd;
    return *this;
}




