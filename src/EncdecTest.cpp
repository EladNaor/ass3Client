//
// Created by alonam on 1/15/17.
//

#include "../include/EncdecTest.h"
#include "../include/MessageEncDec.h"


int main (int argc, char *argv[]) {



    /* * * * * * * * * * * * * * * * * * * * * * * * * * *
                   TESTING THE ENCODER DECODER
                   /* * * * * * * * * * * * * * * * * * * * * * * * * * * */

    // Instructions: 1. Change the names I used for your names.
    //               2. Import the thing you need
    //               3. Remove the "//" from the packet you want to test, and run it.
    //                  You can activate decode and then encode in order to see that you receive the same output as you started.
    //               *. Some of the tests are not relevant - You need to encode just: data, ack, bcast, and error.
    MessageEncDec encdec;
    EncdecTest test;
//  test.testRRQDecode(encdec); // 1
//  test.testWRQDecode(encdec); // 2
//  test.testDataDecode(encdec); // 3
//  test.testDataEncode(encdec); // 3
//  test.testACKDecode(encdec); // 4
// 	test.testACKEncode(encdec); // 4
//  test.testErrorDecode(encdec); // 5
//	test.testErrorEncode(encdec); // 5
// 	test.testDIRQDecode(encdec); // 6
// 	test.testLOGRQDecode(encdec); // 7
// 	test.testDELRQDecode(encdec); // 8
// 	test.testBCastDecode(encdec); // 9
//  test.testBCastEncode(encdec); // 9
//	test.testDISCDecode(encdec); // 10

}


char* EncdecTest::vecToArr(vector<char>& v){
    // Get a char pointer to the data in the vector
    char* buf = &v[0]; // For example , vec[1011,.... , 9101], so buf -> 1011 (Later, i'll send it with the size, so it will know when to finish)
    return buf;
}


vector<char> EncdecTest::arrToVec(char* c){
    int size=sizeof(c);
    vector<char> v (c, c+size);
    return v;
}


//
//void EncdecTest::testDataDecode (EncoderDecoder& encdec){
//    vector<char> b = {0,3,0,2,1,5,1,2}; // 0,2 is the packetSize(2), 1,5 is the blockNum(261)
//    char* x = (char*)03021512;
//    //cout << b << endl;
//    cout << b.size() << endl;
//    cout << "Vector info " << endl;
//    cout << b[6] << endl;
//
//    // bytesToShort({0,5})=(short)5, bytesToShort({1,5})=(short)261
//    ServerPacket* res=nullptr;
//    cout<< "Before decoding, the Arr is"<< endl;
//    printArr(b);
//    cout << "FLAG DataDecode 1" << endl;
//    for (int i=0; i<b.size(); i++) {
//        char tmp = b.at(i);
//        cout << tmp << " Is the fucking nextByte " << endl;
//        res = encdec.decodeNextByte(tmp);
//    }
//    cout << "FLAG DataDecode 2" << endl;
//    DataPacket *res1= dynamic_cast<DataPacket*>(res);
//    cout << "FLAG DataDecode 3" << endl;
//    short opcode=res1->getOpcode();
//    short packetSize=res1->getPacketSize();
//    short blockNum=res1->getBlockNum();
//    vector<char> dataBytes=res1->getData();
//    cout << "FLAG DataDecode 4" << endl;
//    cout<< "After decoding the arr, we've got a packet!"<<endl;
//    cout<<"The opcode is " << opcode << " The packetSize is " << packetSize <<"  and the blockNum is " << blockNum<<endl;
//    cout<<"The data is "<<endl;
//    printArr(dataBytes);
//}



void EncdecTest::testDataDecode (EncoderDecoder& encdec){
    vector<char> b = {0,3,0,5,1,5,1,2,3,4,5}; // 0,5 is the packetSize(5), 1,5 is the blockNum(261)
    // bytesToShort({0,5})=(short)5, bytesToShort({1,5})=(short)261
    Packet* res=nullptr;
    cout<< "Before decoding, the Arr is"<< endl;
    printArr(b);
    cout << "FLAG DataDecode 1" << endl;
    for (int i=0; i<b.size(); i++)
        res=encdec.decodeNextByte(b[i]);
    cout << "FLAG DataDecode 2" << endl;
    Packet *res1= dynamic_cast<Packet*>(res);
    cout << "FLAG DataDecode 3" << endl;
    short opcode=res1->getOpCode();
    short packetSize=res1->getPacketSize();
    short blockNum=res1->getBlockNumber();
    vector<char> dataBytes=res1->getData();
    cout << "FLAG DataDecode 4" << endl;
    cout<< "After decoding the arr, we've got a packet!"<<endl;
    cout<<"The opcode is " << opcode << " The packetSize is " << packetSize <<"  and the blockNum is " << blockNum<<endl;
    cout<<"The data is "<<endl;
    printArr(dataBytes);
}

void EncdecTest::testDataEncode (EncoderDecoder& encdec){
    vector<char> b = {1,2,3,4,5};
    Packet *packet = new Packet();
    packet->createDATApacket(((short)5), ((short)261), b);
    vector<char>* res = encdec.encode(packet);
    cout<<"Encoding the packet " << packet->getOpcode() << " is the Opcode "<< packet->getPacketSize() << " is the packetSize " << packet->getBlockNum() << " is the Block Num " <<endl;
    cout<<"The data arr is " <<endl;
    printArr(b);
    cout<<"Output: "<<endl;

    printArr(*res); // Should be {0,3,0,5,1,5,1,2,3,4,5}
    cout<<"The output should be {0,3,0,5,1,5,1,2,3,4,5}"<<endl;
}


void EncdecTest::testDISCDecode (EncoderDecoder& encdec){
    vector<char> b = {0,10};
    ServerPacket* res=nullptr;
    cout<<"Before decoding, the Arr is"<<endl;
    printArr(b);
    for (int i=0; i<b.size(); i++)
        res=encdec.decodeNextByte(b[i]);
    DiscPacket *res1= dynamic_cast<DiscPacket*>(res);
    short opcode=res1->getOpcode();
    cout<<"After decoding the arr, we've got a packet!"<<endl;
    cout<<"The opcode is " << opcode << endl;
}

void EncdecTest::testDISCEncode (EncoderDecoder& encdec){
    DiscPacket *packet = new DiscPacket((short)10);
    vector<char>* res = encdec.encode(packet);
    cout<<"Encoding the packet " << packet->getOpcode() << " is the Opcode"<<endl;
    cout<<"Output: "<<endl;

    printArr(*res); // Should be {0,10}
    cout<<"The output should be {0,10}"<<endl;
}

void EncdecTest::testBCastDecode (EncoderDecoder& encdec){
    vector<char> b = {0,9,1,66,67,97,115,116,83,116,114,0};
    // popString({66,67,97,115,116,83,116,114})=(String)"BCastStr"
    ServerPacket* res=nullptr;
    cout<<"Before decoding, the Arr is"<<endl;
    printArr(b);
    for (int i=0; i<b.size(); i++)
        res=encdec.decodeNextByte(b[i]);
    BCastPacket *res1= dynamic_cast<BCastPacket*>(res);
    short opcode=res1->getOpcode();
    short deleted_or_added=res1->getDelOrAdd();
    string Filename=res1->getFileName();
    cout<<"After decoding the arr, we've got a packet!"<<endl;
    cout<<"The opcode is " << opcode << " the deleted_or_added is " << deleted_or_added <<"  and the Filename is " << Filename<<endl;
}

void EncdecTest::testBCastEncode (EncoderDecoder& encdec){
    BCastPacket *packet = new BCastPacket(((short)9), (char) 1, "BCastStr");
    vector<char>* res = encdec.encode(packet);
    cout<<"Encoding the packet " << packet->getOpcode() << " is the Opcode " << packet->getDelOrAdd() << " is the deleted_or_added code " << packet->getFileName()<<endl;
    cout<<"Output: "<<endl;

    printArr(*res); // Should be {0,9,1,66,67,97,115,116,83,116,114,0}
    cout<<"The output should be {0,9,1,66,67,97,115,116,83,116,114,0}"<<endl;
}

void EncdecTest::testDELRQDecode (EncoderDecoder& encdec){
    vector<char> b = {0,8,68,97,110,97,0};
    ServerPacket* res=nullptr;
    cout<<"Before decoding, the Arr is"<<endl;
    printArr(b);
    for (int i=0; i<b.size(); i++)
        res=encdec.decodeNextByte(b[i]);
    DELRQPacket *res1= dynamic_cast<DELRQPacket*>(res);
    short opcode=res1->getOpcode();
    string fileName=res1->getFileName();
    cout<<"After decoding the arr, we've got a packet!"<<endl;
    cout<<"The opcode is " << opcode <<" and the fileName is " << fileName<<endl;
}

void EncdecTest::testDELRQEncode (EncoderDecoder& encdec){
    DELRQPacket *packet = new DELRQPacket((short) 8, "Dana");
    vector<char>* res = encdec.encode(packet);
    cout<<"Encoding the packet " << packet->getOpcode() << " Opcode " << packet->getFileName()<<endl;
    cout<<"Output: "<<endl;

    printArr(*res); // Should be {0,8,68,97,110,97,0}
    cout<<"The output should be {0,8,68,97,110,97,0}"<<endl;
}


void EncdecTest::testLOGRQDecode (EncoderDecoder& encdec){
    vector<char> b = {0,7,68,97,110,97,0};
    ServerPacket* res=nullptr;
    cout<<"Before decoding, the Arr is"<<endl;
    printArr(b);
    for (int i=0; i<b.size(); i++)
        res=encdec.decodeNextByte(b[i]);
    LOGRQPacket *res1= dynamic_cast<LOGRQPacket*>(res);
    short opcode=res1->getOpcode();
    string userName=res1->getUserName();
    cout<<"After decoding the arr, we've got a packet!"<<endl;
    cout<<"The opcode is " << opcode <<" and the userName is " << userName<<endl;
}

void EncdecTest::testLOGRQEncode (EncoderDecoder& encdec){
    LOGRQPacket *packet = new LOGRQPacket((short) 7, "Dana");
    vector<char>* res = encdec.encode(packet);
    cout<<"Encoding the packet " << packet->getOpcode() << " Opcode " << packet->getUserName()<<endl;
    cout<<"Output: "<<endl;

    printArr(*res); // Should be {0,7,68,97,110,97,0}
    cout<<"The output should be {0,7,68,97,110,97,0}"<<endl;
}


void EncdecTest::testDIRQDecode (EncoderDecoder& encdec){
    vector<char> b = {0,6};
    ServerPacket* res=nullptr;
    cout<<"Before decoding, the Arr is"<<endl;
    printArr(b);
    for (int i=0; i<b.size(); i++)
        res=encdec.decodeNextByte(b[i]);
    DIRQPacket *res1= dynamic_cast<DIRQPacket*>(res);
    short opcode=res1->getOpcode();
    cout<<"After decoding the arr, we've got a packet!"<<endl;
    cout<<"The opcode is " << opcode<<endl;
}

void EncdecTest::testDIRQEncode (EncoderDecoder& encdec){
    DIRQPacket *packet = new DIRQPacket((short)6);
    vector<char>* res = encdec.encode(packet);
    cout<<"Encoding the packet " << packet->getOpcode() << " is the Opcode"<<endl;
    cout<<"Output: "<<endl;

    printArr(*res); // Should be {0,6}
    cout<<"The output should be {0,6}"<<endl;
}


void EncdecTest::testErrorDecode (EncoderDecoder& encdec){
    vector<char> b = {0,5,14,20 ,69,114,114,111,114,32,75,97,112,97,114,97 ,0};
    // bytesToShort({14,20})=(short)3604, and popString({69,114,114,111,114,32,75,97,112,97,114,97})=(String)"Error Kapara"
    ServerPacket* res=nullptr;
    cout<<"Before decoding, the Arr is"<<endl;
    printArr(b);
    for (int i=0; i<b.size(); i++)
        res=encdec.decodeNextByte(b[i]);
    ErrorPacket *res1= dynamic_cast<ErrorPacket*>(res);
    short opcode=res1->getOpcode();
    short errorCode=res1->getErrorCode();
    string errorMsg=res1->getErrMsg();
    cout<<"After decoding the arr, we've got a packet!"<<endl;
    cout<<"The opcode is " << opcode << " The Error code is " << errorCode <<"  and the error messege is " << errorMsg<<endl;
}

void EncdecTest::testErrorEncode (EncoderDecoder& encdec){
    cout << "I'm at the Error encode" << endl;
    ErrorPacket *packet = new ErrorPacket((short)5, (short)3604, "Error Kapara");
    vector<char>* res = encdec.encode(packet);
    cout<<"Encoding the packet " << packet->getOpcode() << " is the Opcode " << packet->getErrorCode() <<" is the error code " << packet->getErrMsg()<<endl;
    cout<<"Output: "<<endl;

    printArr(*res); // Should be {0,5,14,20 ,69,114 ,114,111,114,32,75,97,112,97,114,97 ,0}
    cout<<"The output should be {0,5,14,20,69,114,114,111,114,32,75,97,112,97,114,97,0}"<<endl;
}

void EncdecTest::testRRQDecode (EncoderDecoder& encdec){
    vector<char> b = {0,1,68,97,110,97,0};
    ServerPacket* res=nullptr;
    cout<<"Before decoding, the Arr is"<<endl;
    printArr(b);
    for (int i=0; i<b.size(); i++)
        res=encdec.decodeNextByte(b[i]);
    RRQPacket *res1= dynamic_cast<RRQPacket*>(res);
    short opcode=res1->getOpcode();
    string fileName=res1->getFileName();
    cout<<"After decoding the arr, we've got a packet!"<<endl;
    cout<<"The opcode is " << opcode <<" and the fileName is " << fileName<<endl;
}

void EncdecTest::testRRQEncode (EncoderDecoder& encdec){
    RRQPacket *packet = new RRQPacket((short) 1, "Dana");
    vector<char>* res = encdec.encode(packet);
    cout<<"Encoding the packet " << packet->getOpcode() << " Opcode " << packet->getFileName()<<endl;
    cout<<"Output: "<<endl;

    printArr(*res); // Should be {0,1,68,97,110,97,0}
    cout<<"The output should be {0,1,68,97,110,97,0}"<<endl;
}

void EncdecTest::testWRQDecode (EncoderDecoder& encdec){
    vector<char> b = {0,2,68,97,110,97,0};
    ServerPacket* res=nullptr;
    cout<<"Before decoding, the Arr is"<<endl;
    printArr(b);
    for (int i=0; i<b.size(); i++)
        res=encdec.decodeNextByte(b[i]);
    WRQPacket *res1= dynamic_cast<WRQPacket*>(res);
    short opcode=res1->getOpcode();
    string fileName=res1->getFileName();
    cout<<"After decoding the arr, we've got a packet!"<<endl;
    cout<<"The opcode is " << opcode <<" and the fileName is " << fileName<<endl;
}

void EncdecTest::testWRQEncode (EncoderDecoder& encdec){
    WRQPacket *packet = new WRQPacket((short) 2, "Dana");
    vector<char>* res = encdec.encode(packet);
    cout<<"Encoding the packet " << packet->getOpcode() << " Opcode " << packet->getFileName()<<endl;
    cout<<"Output: "<<endl;

    printArr(*res); // Should be {0,2,68,97,110,97,0}
    cout<<"The output should be {0,2,68,97,110,97,0}"<<endl;
}

void EncdecTest::testACKDecode (EncoderDecoder& encdec){
    vector<char> b = {0,4,14,20}; // bytesToShort({14,20})=(short)3604
    ServerPacket* res=nullptr;
    cout<<"Before decoding, the Arr is"<<endl;
    printArr(b);
    for (int i=0; i<b.size(); i++)
        res=encdec.decodeNextByte(b[i]);
    AckPacket *res1= dynamic_cast<AckPacket*>(res);
    short opcode=res1->getOpcode();
    short blockNum=res1->getBlockNum();
    cout<<"After decoding the arr, we've got a packet!"<<endl;
    cout<<"The opcode is " << opcode <<" and the blockNum is " << blockNum<<endl;
}

void EncdecTest::testACKEncode (EncoderDecoder& encdec){
    AckPacket *packet = new AckPacket((short) 4, ((short)3604)); // bytesToShort({14,20})=(short)3604
    vector<char>* res = encdec.encode(packet);
    cout<<"Encoding the packet " << packet->getOpcode() << " Opcode " << packet->getBlockNum()<<endl;
    cout<<"Output: "<<endl;

    printArr(*res); // Should be {0,2,68,97,110,97,0}
    cout<<"The output should be {0,4,14,20}"<<endl;
}


void EncdecTest::printArr(vector<char> b){
    //	System.out.print("Output: ");
    string s="";
    for (unsigned int i=0; i<b.size(); i++){
        s= s + b.at(i) + " ";
    }
    cout << s <<endl;
}


short EncdecTest::bytesToShort(vector<char> byteArr)
{
    short result = (short)((byteArr[0] & 0xff) << 8);
    result += (short)(byteArr[1] & 0xff);
    return result;
}

vector<char> EncdecTest::shortToBytes(short num)
{
    vector<char> bytesArr;
    bytesArr.push_back( ((num >> 8) & 0xFF) );
    bytesArr.push_back(  (num & 0xFF)  );
    return bytesArr;

}

vector<char> EncdecTest::popTwoFirstBytes(vector<char> dataToDecode){
    dataToDecode.erase(dataToDecode.begin());
    dataToDecode.erase(dataToDecode.begin());
    return dataToDecode;
}


string EncdecTest::popString(vector<char> bytes) {

    std::string s(bytes.begin(), bytes.end());
    return s;
    //notice that we explicitly requesting that the string will be decoded from UTF-8
    //this is not actually required as it is the default encoding in java.

}

