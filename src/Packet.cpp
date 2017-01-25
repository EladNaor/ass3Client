#include "Packet.h"
#include "../include/Packet.h"

using namespace std;
void Packet::createRRQpacket(const std::wstring &filename) {
    this->opcode = 1;
    this->string = filename;
    this->endByte = true;
}

void Packet::createWRQpacket(const std::wstring &filename) {
    this->opcode = 2;
    this->string = filename;
    this->endByte = true;
}

void Packet::createDATApacket(short packetSize, short blockNumber, std::vector<char> &data) {
    this->opcode = 3;
    this->packetSize = packetSize;
    this->blockNumber = blockNumber;
    this->data = std::vector<char>(data.size());
    for (int i = 0; i < this->data.size(); i++) {
        this->data[i] = data[i];
    }
    this->endByte = true;
}

void Packet::createACKpacket(short numOfBlocks) {
    this->opcode = 4;
    this->blockNumber = numOfBlocks;
    this->endByte = false;
}

void Packet::createERRORpacket(short errCode, const std::wstring &errMsg) {
    this->opcode = 5;
    this->endByte = true;
    this->errCode = errCode;
    this->string = errMsg;
    /* switch(errType){
        case 0: this.string= "Not defined";
        break;
        case 1: this.string= "File not found";
        break;
        case 2: this.string= "Access violation � File cannot be written, read or deleted";
        break;
        case 3: this.string= "Disk full or allocation exceeded � No room in disk";
        break;
        case 4: this.string= "Illegal TFTP operation � Unknown Opcode";
        break;
        case 5: this.string= "File already exists � File name exists on WRQ";
        break;
        case 6: this.string= "User not logged in � Any opcode received before Login completes";
        break;
        case 7: this.string= "User already logged in � Login username already connected";
        break;
    }*/
}

void Packet::createDIRQpacket() {
    this->opcode = 6;
    this->endByte = false;
}

void Packet::createLOGRQpacket(const std::wstring &username) {
    this->opcode = 7;
    this->string = username;
    this->endByte = true;
}

void Packet::createDELRQpacket(const std::wstring &filename) {
    this->opcode = 8;
    this->string = filename;
    this->endByte = true;

}

void Packet::createBCASTpacket(bool isAdded, const std::wstring &filename) {
    this->opcode = 9;
    this->string = filename;
    this->addedOrDeleted = isAdded;
    this->endByte = true;
}

void Packet::createDISCpacket() {
    this->opcode = 10;
    this->endByte = false;
}

void Packet::send() {
    //TODO: send packet
}

short Packet::getOpCode() {
    return this->opcode;
}

std::wstring Packet::getString() {
    return this->string;
}

short Packet::getBlockNumber() {
    return this->blockNumber;
}

short Packet::getPacketSize() {
    return this->packetSize;
}

std::vector<char> Packet::getData() {
    return this->data;
}

short Packet::getErrCode() {
    return this->errCode;
}

bool Packet::getAddedOrDeleted() {
    return this->addedOrDeleted;
}
