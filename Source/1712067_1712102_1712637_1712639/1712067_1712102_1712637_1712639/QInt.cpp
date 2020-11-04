#include "Qint.h"

Qint::Qint()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}

//Set the true position of a QInt's bit
void Qint::SetBit(bool bit, int bit_pos)
{
	if (bit == 1)
		data[bit_pos / 32] = data[bit_pos / 32] | 1 << (31 - bit_pos % 32);

}
bool Qint::GetBit(int i)

{

	return (data[i / 32] >> (31 - i % 32)) & 1;

}
//Divide a decimal string by 2
void DivideTwo(string & dec_str)
{
	for (int i = 0; i < dec_str.length(); i++)
	{
		if ((dec_str[i] - '0') % 2 == 1)
			dec_str[i + 1] = 10 + dec_str[i + 1];

		dec_str[i] = (dec_str[i] - '0') / 2 + '0';

	}
	if (dec_str[0] == '0')
	{
		dec_str.erase(dec_str.begin());
	}

}
//
void Qint::DecimalStringToQInt(string dec_str)
{
	bool bit, neg = false;
	int bit_pos = 127;

	if (dec_str == "0")
		return;

	if (dec_str[0] == '-')
	{
		dec_str.erase(dec_str.begin());
		neg = true;
	}

	while (dec_str != "")
	{
		bit = (dec_str[dec_str.length() - 1] - '0') % 2;
		SetBit(bit, bit_pos);
		DivideTwo(dec_str);
		bit_pos--;
	}

	if (neg == true)
	{
		//Use bitwise NOT operator to convert from positive to negative counterpart of QInt
		//One's complement format
		*this = ~*this;

		//Add 1 to QInt so it becomes two's complement format
		Qint temp;
		temp.SetBit(1, 127);
		*this = *this + temp;
	}
}


//Convert from a binary string to QInt
void Qint::BinaryStringToQInt(string bin_str)
{
	int bin;
	int bit_pos = 127;
	bool bit;
	while (bin_str != "")
	{
		int len = bin_str.length() - 1;
		bin = bin_str[len] - '0';
		if (bin == 0)
			bit = 0;
		if (bin == 1)
			bit = 1;
		SetBit(bit, bit_pos);
		bit_pos--;
		bin_str.erase(bin_str.begin() + len);
	}
}


void Qint::HexadecimalStringToQInt(string hex_str)
{
	string bin_str = "";
	string bin[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	char hex[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	for (int i = 0; i<hex_str.length(); i++)
	{
		for (int j = 0; j<16; j++)
		{
			if (hex_str[i] == hex[j])
			{
				bin_str = bin_str + bin[j];
				break;
			}
		}
	}
	BinaryStringToQInt(bin_str);
}

string Qint::QIntToBinaryString()
{
	string bin_str = "";
	char bit;
	if (data[0] == 0 && data[1] == 0 && data[2] == 0 && data[3] == 0)
		return "0";

	for (int i = 0; i<128; i++)
	{
		if (GetBit(i) == 0)
			bit = '0';
		else
			bit = '1';
		bin_str = bin_str + bit;
	}
	while (bin_str[0] == '0')
		bin_str.erase(bin_str.begin());
	return bin_str;
}
//Convert from QInt to decimal string
string Qint::QIntToDecimalString()
{
	string dec_str = "";
	string bin_str;
	bool neg = false;

	if (data[0] >= 2147483648)
	{
		neg = true;
		Qint temp;
		temp.SetBit(1, 127);
		*this = *this - temp;

		*this = ~*this;
	}

	bin_str = this->QIntToBinaryString();
	int len = bin_str.length() - 1;

	for (int i = len; i >= 0; i--)
		if (bin_str[i] == '1')
			dec_str = AddTwoPositiveDecimalString(BaseTwoExponentN(len - i), dec_str);

	if (neg == true)
		dec_str = "-" + dec_str;

	return dec_str;
}

//Add two positive decimal string
string AddTwoPositiveDecimalString(string a, string b)
{
	string res = "";

	while (a.length() < b.length())
		a = "0" + a;
	while (b.length() < a.length())
		b = "0" + b;

	int len = a.length() - 1;
	int carry = 0;

	for (int i = len; i >= 0; i--)
	{
		int temp = (a[i] - '0') + (b[i] - '0') + carry;
		res = (char)(temp % 10 + '0') + res;
		carry = temp / 10;
	}

	if (carry == 1)
		res = "1" + res;

	return res;
}

//Compute two to the N
string BaseTwoExponentN(int n)
{
	if (n == 0)
		return "1";

	string res = "2";

	for (int i = 1; i < n; i++)
	{
		int len = res.length() - 1;
		int carry = 0;

		for (int j = len; j >= 0; j--)
		{
			res[j] = (res[j] - '0') * 2 + carry;
			carry = res[j] / 10;
			res[j] = res[j] % 10 + '0';
		}

		if (carry != 0)
			res = (char)(carry + '0') + res;
	}

	return res;
}

//Connvert from QInt to hexadecimal string
string Qint::QIntToHexadecimalString()
{
	string bin_str = this->QIntToBinaryString();
	string hex_str = BinaryStringToHexadecimalString(bin_str);

	return hex_str;
}


//Convert from binary string to hexadecimal one
string BinaryStringToHexadecimalString(string bin_str)
{
	if (bin_str.length() % 4 != 0)
	{
		int ii = 4 - (bin_str.length() - (bin_str.length() / 4) * 4);
		for (int i = 0; i < ii; i++)
			bin_str.insert(0, "0");
	}
	string hex_str = "";

	string bin[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	char hex[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	int ii = 0;
	for (int i = 0; i < bin_str.length() / 4; i++)
	{
		string str1 = bin_str.substr(ii, 4);
		for (int j = 0; j<16; j++)
		{
			if (strcmp(bin[j].c_str(), str1.c_str()) == 0)
			{
				hex_str += hex[j];
				ii += 4;
				break;
			}
		}
	}

	return hex_str;
}
//Convert from decimal string to hexadecimal one
string DecimalStringToHeXadecimalString(string dec_str)
{
	string bin_str, hex_str;
	Qint a;
	a.DecimalStringToQInt(dec_str);
	bin_str = a.QIntToBinaryString();
	hex_str = BinaryStringToHexadecimalString(bin_str);
	return hex_str;
}

//+ operator
Qint operator+(const Qint& x1, const Qint& x2)
{
	Qint t1, t2;
	t1 = x1;
	t2 = x2;
	Qint result;
	bool bit_x1, bit_x2, bit, flat = 0;
	for (int i = 127; i >= 0; i--)
	{
		bit_x1 = t1.GetBit(i);
		bit_x2 = t2.GetBit(i);
		bit = bit_x1 ^ bit_x2 ^ flat;
		if ((bit_x1 == 1 && bit_x2 == 1) || (bit_x1 == 1 && flat == 1) || (bit_x2 == 1 && flat == 1)) flat = 1;
		else flat = 0;
		result.SetBit(bit, i);
	}
	return result;
}
////- operator
Qint operator-(const Qint & x1, const Qint & x2)
{
	Qint temp1, temp2;
	temp1 = x2;
	for (int i = 0; i < 4; i++)
		temp1.data[i] = ~temp1.data[i];// lay dang phu dinh cua x2
	temp2.data[3] = 1;
	temp1 = temp1 + temp2;// chuyen thanh dang bu 2
	return x1 + temp1; //tru mot so la cong cho so doi cua no
}
// shift right
Qint operator >> (const Qint& a, int k)
{
	Qint t, A;
	A = a;
	for (int i = 127 - k; i >= 0; i--) {

		t.SetBit(A.GetBit(i), i + k);//dich bit sang phai, bo bit phai nhat
	}
	for (int i = 0; i < k; i++) {

		t.SetBit(0, i);//them 0 o bit trai nhat

	}
	return t;
}
//shift left
Qint operator<<(const Qint& a, int k)
{
	Qint t, A;
	A = a;
	for (int i = k; i < 128; i++)
	{
		t.SetBit(A.GetBit(i), i - k);// dich bit sang trai, bo bit trai nhat
	}
	for (int i = 127 - k + 1; i < 128; i++)
	{
		t.SetBit(0, i);		//them 0 o bit phai nhat
	}
	return t;
}
//rotate left
Qint Qint::RotateLeft(const Qint & a, int k)
{
	Qint t, A;
	A = a;
	int m = 0;
	for (int i = k; i < 128; i++)
	{
		t.SetBit(A.GetBit(i), i - k);//dich bit qua trai
	}
	for (int i = 127 - k + 1; i < 128; i++)
	{
		t.SetBit(A.GetBit(m), i);//bit trai nhat thanh bit phai nhat
		m++;
	}
	return t;
}
//rotate right
Qint Qint::RotateRight(const Qint & a, int k)
{
	Qint t, A;
	A = a;
	int m = 127;
	for (int i = 127 - k; i >= 0; i--) {

		t.SetBit(A.GetBit(i), i + k);//dich bit sang phai
	}
	for (int i = k - 1; i >= 0; i--)
	{

		t.SetBit(A.GetBit(m), i);//bit phai nhat thanh bit trai nhat
		m--;
	}
	return t;
}
void ShiftRight(Qint &A, Qint &Q, bool &Qt)

{

	bool cuoiA = A.GetBit(127); //Bit cuoi cua A

	Qt = Q.GetBit(127); //Bit cuoi cua Q

	A = A >> 1;

	Q = Q >> 1;

	Q.SetBit(cuoiA, 0);

}
// *operator
Qint operator *(Qint &Q, Qint &M)
{
	Qint A;
	bool Qt = 0;
	for (int i = 0; i < 128; i++)
	{
		if (Q.GetBit(128 - 1) == 1 && Qt == 0)
		{
			A = A - M;
		}
		else if (Q.GetBit(128 - 1) == 0 && Qt == 1)
		{
			A = A + M;
		}
		ShiftRight(A, Q, Qt);
	}
	return Q;

}
void ShiftLeft(Qint &A, Qint &Q)
{
	bool dauQ = Q.GetBit(0);
	A = A << 1;
	Q = Q << 1;
	A.SetBit(dauQ, 127);
}
/// operator
Qint operator /(Qint &Q, Qint &M)
{
	Qint A;
	for (int i = 0; i <128; i++)
	{
		ShiftLeft(A, Q);
		A = A - M;
		if (A.GetBit(0) == 1)
		{
			Q.SetBit(0, 127);
			A = A + M;
		}
		else
		{
			Q.SetBit(1, 127);
		}
	}
	return Q;
}
////not operator
Qint Qint::operator~()
{
	Qint result;
	for (int i = 0; i < 128; i++)
	{
		bool bit;
		bit = GetBit(i);
		if (bit == 1) result.SetBit(0, i);//lay phu dinh cua tung bit
		else result.SetBit(1, i);
	}
	return result;
}
////and operator
Qint operator&(const Qint& x1, const Qint& x2)
{
	Qint result, tmp1, tmp2;
	tmp1 = x1;
	tmp2 = x2;
	for (int i = 0; i < 128; i++)
	{
		bool bit_x1, bit_x2;
		bit_x1 = tmp1.GetBit(i);
		bit_x2 = tmp2.GetBit(i);
		if (bit_x1 == 1 && bit_x2 == 1) result.SetBit(1, i);//and voi 0 luon luon bang 0
		else result.SetBit(0, i);
	}
	return result;
}
////or operator
Qint operator|(const Qint& x1, const Qint& x2)
{
	Qint result, tmp1, tmp2;
	tmp1 = x1;
	tmp2 = x2;
	for (int i = 0; i < 128; i++)
	{
		bool bit_x1, bit_x2;
		bit_x1 = tmp1.GetBit(i);
		bit_x2 = tmp2.GetBit(i);
		if (bit_x1 == 1 || bit_x2 == 1) result.SetBit(1, i);//or voi 1 luon luon bang 1
		else result.SetBit(0, i);
	}
	return result;
}
// xor operator
Qint operator^(const Qint& x1, const Qint& x2)
{
	Qint result, tmp1, tmp2;
	tmp1 = x1;
	tmp2 = x2;
	for (int i = 0; i < 128; i++)
	{
		bool bit_x1, bit_x2;
		bit_x1 = tmp1.GetBit(i);
		bit_x2 = tmp2.GetBit(i);
		if ((bit_x1 == 1 && bit_x2 == 1) || (bit_x1 == 0 && bit_x2 == 0)) result.SetBit(0, i);//2 bit cung dau thi xor bang 0
		else result.SetBit(1, i);
	}
	return result;
}
//<operator
bool operator<(const Qint& x1, const Qint& x2)
{
	Qint tmp1, tmp2;
	tmp1 = x1;
	tmp2 = x2;
	if (tmp1.GetBit(0) == tmp2.GetBit(0))//cung dau
	{
		if (tmp1.GetBit(0) == 0)
		{
			for (int i = 1; i < 128; i++)
			{
				if (tmp1.GetBit(i) < tmp2.GetBit(i)) return true;//ca hai cung duong
			}
		}
		else
		{
			for (int i = 1; i < 128; i++)
			{
				if (tmp1.GetBit(i) > tmp2.GetBit(i)) return true;//ca hai cung am
			}
		}
	}
	else if (tmp1.GetBit(0) == 1) return true;//khac dau
	return false;
}
//>operator
bool operator>(const Qint& x1, const Qint& x2)
{
	Qint tmp1, tmp2;
	tmp1 = x1;
	tmp2 = x2;
	if (tmp1.GetBit(0) == tmp2.GetBit(0))
	{
		if (tmp1.GetBit(0) == 0)
		{
			for (int i = 1; i < 128; i++)
			{
				if (tmp1.GetBit(i) > tmp2.GetBit(i)) return true;
			}
		}
		else
		{
			for (int i = 1; i < 128; i++)
			{
				if (tmp1.GetBit(i) < tmp2.GetBit(i)) return true;
			}
		}
	}
	else if (tmp1.GetBit(0) == 0) return true;
	return false;
}
//==operator
bool operator==(const Qint& x1, const Qint& x2)
{
	Qint tmp1, tmp2;
	tmp1 = x1;
	tmp2 = x2;
	if (!(tmp1<tmp2) && !(tmp1>tmp2)) return true;//khi no khong nho hon cung khong lon hon
	return false;
}
//<=operator
bool operator<=(const Qint& x1, const Qint& x2)
{
	Qint tmp1, tmp2;
	tmp1 = x1;
	tmp2 = x2;
	if (tmp1<tmp2 || tmp1 == tmp2) return true;//khi no nho hon hoac bang
	return false;
}
//>= operator
bool operator>=(const Qint& x1, const Qint& x2)
{
	Qint tmp1, tmp2;
	tmp1 = x1;
	tmp2 = x2;
	if (tmp1>tmp2 || tmp1 == tmp2) return true;
	return false;
}
//= operator
Qint Qint::operator=(const Qint& x1)
{
	for (int i = 0; i < 4; i++)
	{
		this->data[i] = x1.data[i];
	}
	return *this;
}
//
void Scan(Qint &q, string str, int base)
{
	switch (base)
	{
	case 2:
		q.BinaryStringToQInt(str);
		break;
	case 10:
		q.DecimalStringToQInt(str);
		break;
	case 16:
		q.HexadecimalStringToQInt(str);
		break;
	}
}


//

void Print(ofstream & outfile, Qint q, int base)
{
	switch (base)
	{
	case 2:
		outfile << q.QIntToBinaryString();
		break;
	case 10:
		outfile << q.QIntToDecimalString();
		break;
	case 16:
		outfile << q.QIntToHexadecimalString();
		break;
	}
}
