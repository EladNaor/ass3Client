//
// Created by alonam on 1/15/17.
//

#ifndef CLIENTDANA_ENCDECTEST_H
#define CLIENTDANA_ENCDECTEST_H
#include "../include/EncoderDecoder.h"
using namespace std;
#include <string>
#include <iostream>


class EncdecTest {

public:
    EncoderDecoder* encdec = new EncoderDecoder();
     char* vecToArr(vector<char>& v);
     vector<char> arrToVec(char* c);
     void testDataDecode (EncoderDecoder& encdec);
     void testDataEncode (EncoderDecoder& encdec);
     void testDISCDecode (EncoderDecoder& encdec);
     void testDISCEncode (EncoderDecoder& encdec);
     void testBCastDecode (EncoderDecoder& encdec);
     void testBCastEncode (EncoderDecoder& encdec);
     void testDELRQDecode (EncoderDecoder& encdec);
     void testDELRQEncode (EncoderDecoder& encdec);
     void testLOGRQDecode (EncoderDecoder& encdec);
     void testLOGRQEncode (EncoderDecoder& encdec);
     void testDIRQDecode (EncoderDecoder& encdec);
     void testDIRQEncode (EncoderDecoder& encdec);
     void testErrorDecode (EncoderDecoder& encdec);
     void testErrorEncode (EncoderDecoder& encdec);
     void testRRQDecode (EncoderDecoder& encdec);
     void testRRQEncode (EncoderDecoder& encdec);
     void testWRQDecode (EncoderDecoder& encdec);
     void testWRQEncode (EncoderDecoder& encdec);
     void testACKDecode (EncoderDecoder& encdec);
     void testACKEncode (EncoderDecoder& encdec);
     void printArr(vector<char> b);
     short bytesToShort(vector<char> byteArr);
     vector<char> shortToBytes(short num);
     vector<char> popTwoFirstBytes(vector<char> dataToDecode);
     string popString(vector<char> bytes);

};


#endif //CLIENTDANA_ENCDECTEST_H