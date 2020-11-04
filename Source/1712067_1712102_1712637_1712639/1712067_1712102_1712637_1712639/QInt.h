#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class Qint
{
public:
	unsigned int data[4];
	Qint();

	//Input
	void SetBit(bool bit, int bit_pos);
	bool GetBit(int i);
	void BinaryStringToQInt(string bin_str);
	void DecimalStringToQInt(string dec_str);
	void HexadecimalStringToQInt(string hex_str);
	//Output
	string QIntToBinaryString();
	string QIntToDecimalString();
	string QIntToHexadecimalString();
	//Shift
	//Rotate
	Qint RotateLeft(const Qint & a, int k);
	Qint RotateRight(const Qint & a, int k);
	////operator
	friend Qint operator+(const Qint& x1, const  Qint& x2);
	friend Qint operator-(const Qint& x1, const Qint& x2);
	friend Qint operator *(Qint &Q, Qint &M);
	friend Qint operator /(Qint &Q, Qint &M);
	friend Qint operator >> (const Qint& Q, int k);
	friend Qint operator<<(const Qint& Q, int k);
	Qint operator~();
	friend Qint operator&(const Qint& x1, const Qint& x2);
	friend Qint operator|(const Qint& x1, const Qint& x2);
	friend Qint operator^(const Qint& x1, const Qint& x2);
	friend bool operator < (const Qint& x1, const Qint& x2);
	friend bool operator<=(const Qint& x1, const Qint& x2);
	friend bool operator>(const Qint& x1, const Qint& x2);
	friend bool operator>=(const Qint& x1, const Qint& x2);
	friend bool operator==(const Qint& x1, const Qint& x2);
	Qint operator=(const Qint& x1);
};
void DivideTwo(string & dec_str);
string AddTwoPositiveDecimalString(string a, string b);
string BaseTwoExponentN(int n);
string BinaryStringToHexadecimalString(string bin_str);
string DecimalStringToHeXadecimalString(string dec_str);
void Scan(Qint &q, string str, int base);
void Print(ofstream & outfile, Qint q, int base);