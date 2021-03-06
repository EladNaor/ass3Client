#pragma once

#include <string>
#include <vector>


class Packet {
public:
    //All fields associated with a given packet
private:
    short opcode = 0;
    short blockNumber = 0;
    std::string string;
    // true if the packet has 1 byte of 0 there
    bool endByte = false;
    //only for BCAST packet
    bool addedOrDeleted = false;
    //only for DATA packet
    std::vector<char> data;
    short packetSize = 0;
    //only for ERROR packet
    short errCode = 0;


    //Client requests to read from server
    static constexpr short RRQopcode = 1;
    //Client requests to write to server
    static constexpr short RRWopcode = 2;
    //Client to server upload or server to client download of data;
    static constexpr short DATAopcode = 3;
    //Acknowledges a msg has been received
    static constexpr short ACKopcode = 4;
    //Some kind of Error occurred
    static constexpr short ERRORopcode = 5;
    //Return a string list of all files in the File directory(using a data packet to do so)
    static constexpr short DIRQopcode = 6;
    //logs in to server using a Username
    static constexpr short LOGRQopcode = 7;
    //Clients asks to delete a specific file from server
    static constexpr short DELRQopcode = 8;
    //A server msg to all logged clients notifying a file has been added/deleted
    static constexpr short BCASTopcode = 9;
    //Client asking server to terminate
    static constexpr short DISCopcode = 10;

    //maximum size of a single data sent through the DATA packet
    static constexpr int MaxDataBlockByteSize = 512;


public:

    Packet();
    void createRRQpacket(std::string filename);

    void createWRQpacket(std::string filename);

    void createDATApacket(short packetSize, short blockNumber, std::vector<char> &data);

    void createACKpacket(short numOfBlocks);

    void createERRORpacket(short errCode, std::string errMsg);

    void createDIRQpacket();

    void createLOGRQpacket(std::string username);

    void createDELRQpacket(std::string filename);

    void createBCASTpacket(bool isAdded, std::string filename);

    void createDISCpacket();


    void send();

    short getOpCode();

    std::string getString();

    short getBlockNumber();

    short getPacketSize();

    std::vector<char> * getData();

    short getErrCode();

    bool getAddedOrDeleted();


};
