#pragma once
#include <string>
#include <vector>
#include "Packet.h"

using namespace std;
/// <summary>
/// Created by Dor on 1/25/2017.
/// </summary>
class MessageEncDec {

private:
    Packet *p = nullptr;
    short opCode = 0;

    std::vector<char> bytesOfOpCode();
    int i = 0;
    //ByteBuffer *byteBuffer;

    //For DATA Packets:
    int j = 0;
    int counter = 0;
    short packetSize = 0;
    short blockNumber = 0;

    std::vector<char> bytesOfDataPacketSize();

    std::vector<char> bytesOfBlockNumber();
    //ByteBuffer *data = ByteBuffer::allocate(512);


    //for ERROR Packets
    int k = 0;
    short errCode = 0;

    std::vector<char> bytesOfErrorCode();

    //For Encoder
    std::vector<char> ans;

    //For BCAST Packet
    bool delOrAdd = false;


public:
    virtual ~MessageEncDec() {
        delete p;
     //   delete byteBuffer;
  //      delete data;
    }

    virtual void errorInit();

    virtual void init();

    virtual void dataInit();

    virtual Packet *decodeNextByte(char nextByte);

private:
  //  std::wstring byteBufferToChar(ByteBuffer *byteBuffer);

public:
    virtual std::vector<char> encode(Packet *message);

    short bytesToShort(char *bytesArr);

    void shortToBytes(short num, char *bytesArr);
};
