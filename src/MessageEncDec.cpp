#include "../include/MessageEncDec.h"

void MessageEncDec::errorInit() {
    k = 0;
   // bytesOfErrorCode = std::vector<char>(2);
}

void MessageEncDec::init() {
//    p = nullptr;
//    delOrAdd = false;
//    bytesOfOpCode = std::vector<char>(2);
//    i = 0;
//    byteBuffer = ByteBuffer::allocate(512);
}

void MessageEncDec::dataInit() {
    j = 0;
    counter = 0;
//    bytesOfDataPacketSize = std::vector<char>(2);
//    bytesOfBlockNumber = std::vector<char>(2);
//    data = ByteBuffer::allocate(512);
}

Packet *MessageEncDec::decodeNextByte(char nextByte) {
//    if (opCode == 0) {
//        bytesOfOpCode[i] = nextByte;
//        i++;
//        if (i == 2) {
//            opCode = bytesToShort(bytesOfOpCode);
//            init();
//
//            if (opCode == 6) {
//                Packet *p2 = new Packet();
//                p2->createDIRQpacket();
//                opCode = 0;
//                return p2;
//            }
//
//            if (opCode == 10) {
//                Packet *p2 = new Packet();
//                p2->createDISCpacket();
//                opCode = 0;
//                return p2;
//            }
//        }
//        return nullptr;
//    }
//
//    switch (opCode) {
//        case 1: {
//            if (nextByte != 0) {
//                byteBuffer->put(nextByte);
//                return nullptr;
//            } else {
//                std::wstring fileName = byteBufferToChar(byteBuffer);
//                p = new Packet();
//                p->createRRQpacket(fileName);
//                opCode = 0;
//                return p;
//            }
//        }
//
//        case 2: {
//            if (nextByte != 0) {
//                byteBuffer->put(nextByte);
//                return nullptr;
//            } else {
//                std::wstring fileName = byteBufferToChar(byteBuffer);
//                p = new Packet();
//                p->createWRQpacket(fileName);
//                opCode = 0;
//                return p;
//            }
//        }
//
//        case 3: {
//            if (j < 4) {
//                if (j == 0 || j == 1) {
//                    bytesOfDataPacketSize[j] = nextByte;
//                    j++;
//                    return nullptr;
//                }
//                if (j == 2 || j == 3) {
//                    bytesOfBlockNumber[j - 2] = nextByte;
//                    if (j == 3) {
//                        packetSize = bytesToShort(bytesOfDataPacketSize);
//                        blockNumber = bytesToShort(bytesOfBlockNumber);
//                    }
//                    j++;
//                    return nullptr;
//                }
//            } else {
//                if (counter <= packetSize) {
//                    data->put(nextByte);
//                    counter++;
//
//                    if (counter == packetSize) {
//                        p = new Packet();
//                        p->createDATApacket(packetSize, blockNumber, byteBufferToChar(data).getBytes());
//                        dataInit();
//                        opCode = 0;
//                        return p;
//                    }
//                    return nullptr;
//                }
//            }
//        }
//
//        case 4: {
//            if (k == 0 || k == 1) {
//                bytesOfBlockNumber[k] = nextByte;
//                k++;
//                if (k == 2) {
//                    blockNumber = bytesToShort(bytesOfBlockNumber);
//                    p = new Packet();
//                    p->createACKpacket(blockNumber);
//                    opCode = 0;
//                    errorInit();
//                    return p;
//                }
//                return nullptr;
//            }
//        }
//
//        case 5: {
//            if (k < 2) {
//                bytesOfErrorCode[k] = nextByte;
//                k++;
//                return nullptr;
//            }
//            if (k == 2) {
//                errCode = bytesToShort(bytesOfErrorCode);
//                k++;
//            }
//            if (nextByte != 0) {
//                byteBuffer->put(nextByte);
//                return nullptr;
//            } else {
//                std::wstring errMsg = byteBufferToChar(byteBuffer);
//                p = new Packet();
//                p->createERRORpacket(errCode, errMsg);
//                opCode = 0;
//                errorInit();
//                return p;
//            }
//        }
//
//        case 7: {
//            if (nextByte != 0) {
//                byteBuffer->put(nextByte);
//                return nullptr;
//            } else {
//                std::wstring userName = byteBufferToChar(byteBuffer);
//                p = new Packet();
//                p->createLOGRQpacket(userName);
//                opCode = 0;
//                return p;
//            }
//        }
//
//        case 8: {
//            if (nextByte != 0) {
//                byteBuffer->put(nextByte);
//                return nullptr;
//            } else {
//                std::wstring fileName = byteBufferToChar(byteBuffer);
//                p = new Packet();
//                p->createDELRQpacket(fileName);
//                opCode = 0;
//                return p;
//            }
//        }
//
//        case 9: {
//            if (j == 0 && nextByte == 1) {
//                delOrAdd = true;
//                j++;
//                return nullptr;
//            }
//            if (nextByte != 0) {
//                byteBuffer->put(nextByte);
//                return nullptr;
//            } else {
//                std::wstring fileName = byteBufferToChar(byteBuffer);
//                p = new Packet();
//                p->createBCASTpacket(delOrAdd, fileName);
//                opCode = 0;
//                j = 0;
//                return p;
//            }
//        }
//    }
//    return nullptr;
}
//
//std::wstring MessageEncDec::byteBufferToChar(ByteBuffer *byteBuffer) {
//    byteBuffer->flip();
//    std::vector<char> username(byteBuffer->limit());
//    for (int i = 0; i < username.size(); i++) {
//        username[i] = byteBuffer->get(i);
//    }
//    std::wstring ans = L"";
////    try {
//        ans = std::wstring(username, L"UTF-8");
////    }
////    catch (const UnsupportedEncodingException &e) {
////        e->printStackTrace();
////    }
//    return ans;
//}

std::vector<char> MessageEncDec::encode(Packet *message) {
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


short MessageEncDec::bytesToShort(char* bytesArr)
{
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

void MessageEncDec::shortToBytes(short num, char* bytesArr)
{
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}