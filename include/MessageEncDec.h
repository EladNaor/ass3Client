#pragma once
#include <string>
#include <vector>
#include "Packet.h"
using namespace::std;

/// <summary>
/// Created by Dor on 1/25/2017.
/// </summary>


class MessageEncDec {

private:
    Packet *p = nullptr;
    short opCode = 0;
    std::vector<char>* charOfOpCode;
    unsigned int i = 0;
    std::vector<char>* charBuffer;

    //For DATA Packets:
    unsigned int j = 0;
    unsigned int counter = 0;
    short packetSize = 0;
    short blockNumber = 0;
    std::vector<char> *charsOfDataPacketSize;
    std::vector<char> *charsOfBlockNumber;
    std::vector<char> *data = new std::vector<char>();

    //for ERROR Packets
    unsigned int k = 0;
    short errCode = 0;
    std::vector<char> *charsOfErrorCode;

    //For Encoder
    std::vector<char> ans;

    //For BCAST Packet
    bool delOrAdd = false;


public:
    virtual ~MessageEncDec();


    virtual void errorInit();

    virtual void init();

    virtual void dataInit();

    virtual Packet *decodeNextByte(char nextByte);

    virtual std::vector<char> * encode(Packet *message);

    short bytesToShort(char *bytesArr);

    void shortToBytes(short num, vector<char>* bytesArr);

private:
    std::string charBufferToString(std::vector<char> *charBuffer);

    char* vecToArr(std::vector<char>& vector1);

    std::vector<char> arrToVec(char* c);
};
