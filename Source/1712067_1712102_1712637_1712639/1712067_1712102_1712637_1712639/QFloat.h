#pragma once
#include <iostream>
#include <string>
#define MAX 128

//// QFLOAT ////
#define E 15
#define BIAS 16383
const int BITS = 128;

using namespace std;

class QFloat
{
private:
	unsigned int number[4] = { 0 };
public:
	void ScanQFloat(int);
	void PrintQFloat(int);
	string decToBin_q(string& A);
	string binToDec_q(string& A);

};
int getBit(unsigned int x, int i);
void setBit(unsigned int & x, int i);
string decimalPlusDecimal(string& A, string& B);
string binaryPlusOne(string& A);
string decimalMultiplyTwo(string& A);
string tenPowDec(int vtri);
string twoPowDec(int vtri);
string decDivTwoPow(string&A, int vtri);
string decStringDivTwo(string& A);
string binStringToDec(string& A);
string decToBinString(string& A, int numBit = MAX);