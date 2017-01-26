//
// Created by alonam on 1/15/17.
//

#ifndef CLIENTDANA_ENCDECTEST_H
#define CLIENTDANA_ENCDECTEST_H
using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include "MessageEncDec.h"


class EncdecTest {

public:
    MessageEncDec* encdec = new MessageEncDec();
     char* vecToArr(vector<char>& v);
     vector<char> arrToVec(char* c);
     void testDataDecode (MessageEncDec& encdec);
     void testDataEncode (MessageEncDec& encdec);
     void testDISCDecode (MessageEncDec& encdec);
     void testDISCEncode (MessageEncDec& encdec);
     void testBCastDecode (MessageEncDec& encdec);
     void testBCastEncode (MessageEncDec& encdec);
     void testDELRQDecode (MessageEncDec& encdec);
     void testDELRQEncode (MessageEncDec& encdec);
     void testLOGRQDecode (MessageEncDec& encdec);
     void testLOGRQEncode (MessageEncDec& encdec);
     void testDIRQDecode (MessageEncDec& encdec);
     void testDIRQEncode (MessageEncDec& encdec);
     void testErrorDecode (MessageEncDec& encdec);
     void testErrorEncode (MessageEncDec& encdec);
     void testRRQDecode (MessageEncDec& encdec);
     void testRRQEncode (MessageEncDec& encdec);
     void testWRQDecode (MessageEncDec& encdec);
     void testWRQEncode (MessageEncDec& encdec);
     void testACKDecode (MessageEncDec& encdec);
     void testACKEncode (MessageEncDec& encdec);
     void printArr(vector<char> b);
     short bytesToShort(vector<char> byteArr);
     vector<char> shortToBytes(short num);
     vector<char> popTwoFirstBytes(vector<char> dataToDecode);
     string popString(vector<char> bytes);

};


#endif //CLIENTDANA_ENCDECTEST_H