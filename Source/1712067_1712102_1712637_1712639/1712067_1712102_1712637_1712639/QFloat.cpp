#include "QFloat.h"


// Hàm dùng để bật bit thứ  i của số x
void setBit(unsigned int & x, int i)
{
	x = x | (1 << (BITS / 4 - i - 1));
}

// Hàm dùng để lấy bit thứ I của số x là 1 hay 0
int getBit(unsigned int x, int i)
{
	return (x >> (BITS / 4 - i - 1)) & 1;
}

// Hàm cộng chuỗi nhị phân cho một
//  111 + 1
// sur = 1
// Lặp 3 lần i = 2 -> 0
// temp = res[2] - 48 = 1, res[2] = 1!=1 = 0 + 48 ('0'), sur = 1&&1 = 1
// temp = res[1] - 48 = 1, res[1] = 1!=1 = 0 + 48 ('0'), sur = 1&&1 = 1
// temp = res[0] - 48 = 1, res[0] = 1!=1 = 0 + 48 ('0'), sur = 1&&1 = 1
// Hết vòng lặp
// Sur = 1 => res = '1' + res
// res = 1000
string binaryPlusOne(string& A)
{
	char sur = 1; // Số dư,  vì là phép tính cộng một nên khỏi tạo với giá trị ban đầu là một
	char temp;
	string result = A;
	// Lấy từng kí tự trong chuỗi tương đương các bit từ cuối chuỗi
	for (int i = result.length() - 1; i >= 0; i--)
	{
		temp = result[i] - 48; // Gán temp bằng kí tự i trong chuỗi 
		result[i] = (sur != temp) + 48; // sur = 1 và temp = 1 (1 + 1 = 0) => 0; sur = 0, temp = 0 => 0; ...
		sur = temp && sur; // Gán số dư: temp = 1, sur = 1 => sur = 1; temp = 0, sur = 1 => sur = 0; ...
	}
	// Nếu sau khi cộng đến phần tử 0 mà vẫn còn dư
	if (sur == 1)
	{
		result = '1' + result;
	}
	return result;
}

// Hàm cộng hai chuỗi số thập phân dương
// 12 + 90
// sur = 0, na = 1, nb = 1
// Lặp
// na = 1 > -1, nb = 1 > -1, res = '2' + res, temp = 2, sur = 0, na--, nb--
// na = 0 > -1, nb = 0 > -1, res = '0' + res, temp = 0, sur = 1, na--, nb--
// na = -1, nb = -1, sur > 0, res = '1' + res => res = "102"
string decimalPlusDecimal(string& A, string& B)
{
	// KHÔNG CỘNG SỐ ÂM
	int na = A.length() - 1;
	int nb = B.length() - 1;
	char temp;
	char sur = 0; // Số dư
	string result; // Chuỗi kết quả

		// Lặp
	while (1)
	{
		// Nếu cả 2 chuỗi còn phần tử
		if (na > -1 && nb > -1)
		{
			temp = A[na] + B[nb] - 48 - 48 + sur; // Gán temp bằng tổng hai phần tử tương ứng hai chuỗi với số dư
			sur = temp / 10;  // Lấy số dư
			temp = temp % 10; // Lấy phần còn lại
			result = (char)(temp + 48) + result; // Thêm phần tử vào chuỗi
		}

		// Nếu chuỗi B hết phần tử A còn 
		if (na > -1 && nb <= -1)
		{
			temp = A[na] - 48 + sur; // Gán temp bằng tổng số dư với phần tử trong A
			sur = temp / 10; // Lấy dư
			temp = temp % 10;
			result = (char)(temp + 48) + result; // Thêm vào chuỗi
		}
		// Tương tự với trường hợp trên

		if (na <= -1 && nb > -1)
		{
			temp = B[nb] - 48 + sur;
			sur = temp / 10;
			temp = temp % 10;
			result = (char)(temp + 48) + result;
		}

		// Khi hai chuỗi đều hết phần tử
		if (na <= -1 && nb <= -1)
		{
			// Nếu vẫn còn số dư
			if (sur > 0)
			{
				result = (char)(sur + 48) + result; // Thêm phần tử vào kết quả bằng số dư
			}
			// Thoát khỏi vòng lặp

			break;
		}
		na--;
		nb--;
	}
	return result;
}

// Hàm nhân số thập phân cho hai
string decimalMultiplyTwo(string& A)
{
	// Bằng nó cộng chính nó
	string B = decimalPlusDecimal(A, A);
	return B;
}

// Hàm lấy 2 ^ (vtri)
// Chỉ dùng cho vtri không âm
string twoPowDec(int vtri)
{
	int i;
	string result = "1"; // Khởi tạo với giá trị là 1 vì vtri = 0 => 2^0 = 1
						 // Nhân hai vtri lần
	for (i = 0; i < vtri; i++)
	{
		result = decimalMultiplyTwo(result);
	}
	return result;
}

// Hàm chuyển dãy nhị phân sang thập phân
//  A = "10"
//  A.length() = 2 < 128 => dãy bit số dương neg = 0
//  i = 0, A[i] = '1' ^ 48 = 1 => 1*(2^(2 - 0 - 1) = 2
//  i = 1, A[i] = '0' ^ 48 = 0 => 0
// 2 + 0 = 2 => kq: 2
string binStringToDec(string& A)
{
	char neg = 0; // 0: dương, 1: âm
	int i;
	string result = "0";
	string mul = "0";
	string temp = A;

	// Kiểm tra số bit có trong dãy, nếu không đủ mặc định là số dương
	if (temp.length() == MAX)
	{
		// Nếu bit đầu là 1
		if (temp[0] - 48)
		{
			// Gán giá trị tương ứng
			neg = 1;
			// Lấy bù một
			for (int i = 0; i < temp.length(); i++)
			{
				temp[i] = (temp[i] ^ '1') + 48;
			}

			// Bù hai
			temp = binaryPlusOne(temp);
		}
	}

	// Chuyển dãy bit sang số thập phân không âm
	for (i = 0; i < temp.length(); i++)
	{
		if (temp[i] ^ 48)
		{
			mul = twoPowDec(A.length() - i - 1);
			result = decimalPlusDecimal(result, mul);
		}
	}
	// Nếu là dãy bit số âm thêm dấu '-' vào kết quả
	if (neg)
	{
		result = '-' + result;
	}
	return result;
}

// Hàm chuyển từ thập phân sang nhị phân đủ MAX bit
// 2
// temp[0] != '-' => neg = 0
// res = ('2' - 48) % 2 + 48 + res = "0", temp = temp / 2 = 1
// Hết lặp
// res = temp + res = "10"
string decToBinString(string& A, int numBit)
{
	char neg = 0;  // 0: dương, 1: âm
	int sur;
	string result;
	string temp = A;

	// Nếu ký tự đầu là '-' thì neg = 1 xoá kí tự ra khỏi chuỗi
	if (A[0] == '-')
	{
		neg = 1;
		temp.erase(0, 1);
	}
	// Thực hiện vòng Lặp cho đến khi chuỗi temp không chia 2 được nữa
	while (temp != "0" && temp != "1")
	{
		// Thêm vào kết quả kí tự tương ứng, nếu là số lẻ thêm vào '1' chẵn thêm vào '0'
		result = (char)(((temp[temp.length() - 1] - 48) % 2) + 48) + result;
		// Chia temp cho hai
		temp = decStringDivTwo(temp);
	}
	// Cộng thêm phần dư cuối '0' hoặc '1'
	result = temp + result;
	// Thêm vào số lượng kí tự tương ứng để đủ số bit là MAX = 128
	int nc = result.length();
	for (int i = 0; i < numBit - nc; i++)
	{
		result = '0' + result;
	}
	// Nếu là số âm thì ta lấy bù hai của dãy bit
	if (neg == 1)
	{
		for (int i = 0; i < result.length(); i++)
		{
			result[i] = (result[i] == 48) + 48;
		}
		result = binaryPlusOne(result);
	}
	return result;
}

// Hàm tính 10 ^ (vtri)
string tenPowDec(int vtri)
{
	string result;
	result += '1';
	// Thêm số không vào cuối chuỗi
	for (int i = 0; i < vtri; i++)
	{
		result += '0';
	}
	return result;
}

// Hàm chia dãy số thập phân cho hai
// A = "100"
// A != "0" && A != "1"
// i = 0, A[0] = 1, temp = 1, sur = 1%2 = 1, temp / 2 < 0 && i == 0
// i = 1, A[1] = 0, temp = 0 + 10*1 = 10, sur = 10%2 = 0, temp / 2 = 5 => res += '5'
// i = 2, A[2] = 0, temp = 0, sur = 0, i > 0 => res += '0'
// res = "50"
string decStringDivTwo(string& A)
{

	char sur = 0;
	char temp;
	string result;
	// Kiểm tra nếu số là 1 hoặc 2 thì kết quả là 0
	if (A == "0" || A == "1")
	{
		result = "0";
	}
	// Lặp toàn bộ chuỗi rồi lấy từng số chia cho hai
	for (int i = 0; i < A.length(); i++)
	{
		// Lấy từng kí số chuyển sang số lưu vào temp và cộng cho phần dư
		temp = (A[i] - 48) + 10 * sur;
		// Tính phần dư
		sur = temp % 2;

		if (temp / 2 > 0 || i > 0)
		{
			result = result + (char)(temp / 2 + 48);
		}
	}
	return result;
}

// Hàm chia một số cho 2 ^ (vtri)
string decDivTwoPow(string&A, int vtri)
{
	string result = A;
	// Chia hai index lần
	for (int i = 0; i < vtri; i++)
	{
		result = decStringDivTwo(result);
	}
	return result;
}

// Hàm chuyển chuỗi số thực thập phân sang nhị phân
string QFloat::decToBin_q(string& A)
{
	int i = 0;
	int neg = 0;
	int s;
	int p;
	string result;
	string tempFrac;
	string temp2;

	// Phần dấu: kiểm tra số âm
	if (A[i] == '-')
	{
		i++;
		neg = 1;
		result += '1';
	}
	else
	{
		result += '0';
	}

	// Xét trường hợp đặc biệt: inf, nan, ...
	if (A == "-inf")
	{
		result += '1';
		for (i = 0; i < E; i++)
		{
			result += '1';
		}
		for (i = 0; i < MAX - E - 1; i++)
		{
			result += '0';
		}
		return result;
	}
	else if (A == "+inf" && A == "inf")
	{
		result += '0';
		for (i = 0; i < E; i++)
		{
			result += '1';
		}
		for (i = 0; i < MAX - E - 1; i++)
		{
			result += '0';
		}
		return result;
	}

	// Phần nguyên: đưa màng chuỗi tempFrac
	while (A[i] != '.' && i < A.length())
	{
		tempFrac += A[i];
		i++;
	}
	// Chuyển phần nguyên thành chuỗi nhị phân
	tempFrac = decToBinString(tempFrac, 0);
	i++;
	// Phần mũ
	int lcur = 0;
	// Xác định phần mũ dựa theo phần nguyên
	lcur = tempFrac.length() - 1;

	// Phần thập phân: đưa vào chuỗi temp2
	while (i < A.length())
	{
		temp2 += A[i];
		i++;
	}

	// Nếu phần nguyên là 0 thì xét lại phần mũ
	if ((lcur == 0) && tempFrac[0] == '0')
	{
		int lcur2 = temp2.length();

		while (temp2.length() <= lcur2)
		{
			string oldtemp2 = temp2;
			temp2 = decimalMultiplyTwo(temp2);
			// Xét trường hợp số 0
			if (temp2 == oldtemp2)
			{
				if (tempFrac == "0")
				{
					// Lưu bằng phương pháp số quá K
					lcur -= BIAS;
				}
				break;
			}
			lcur--;
		}
		temp2.erase(0, 1);
	}
	lcur += BIAS; // Cộng cho độ lệch

	 // Đưa phần mũ dạng nhị phân vào chuỗi kết quả 010000111001001
	for (int j = 0; j < E; j++)
	{
		result = result + (char)(((lcur >> (E - j - 1)) & 1) + 48);
	}
	int lcur2 = temp2.length();

	// Trường hợp phần mũ dương thì dời dấu chấm một khoảng tương ứng để đưa về dạng chuẩn
	if (lcur - BIAS >= 0)
	{
		result += tempFrac.substr(1, tempFrac.length() < MAX - 1 - E ? tempFrac.length() : MAX - 1 - E);
	}
	// Chuyển và đưa phần định trị vào chuỗi kết quả
	for (int j = 0 + (lcur - BIAS < 0 ? 0 : lcur - BIAS); j < MAX - 1 - E; j++)
	{
		temp2 = decimalMultiplyTwo(temp2);
		if (temp2.length() > lcur2)
		{
			result += '1';
			temp2.erase(0, 1);
		}
		else
		{
			result += '0';
		}
	}
	return result;
}

// Hàm chuyển số thực nhị phân sang thập phân
string QFloat::binToDec_q(string& A)
{
	int i;
	int expo;
	int checkE = 0;
	string result;
	string s;		string p;
	string temp;	string temp2;
	string B;
	// Xét số đặc biệt
	// Xét phần mũ
	for (i = 1; i < E + 1; i++)
	{
		checkE += A[i] - 48;  // checkE == 15 phần mũ toàn một, checkE == 0 phần mũ toàn bit không
	}
	// Xét phần định trị nếu có một bit khác không thì thoát vòng lập
	for (i = 0; i < A.length(); i++)
	{
		if (A[i] != 0)
		{
			break;
		}
	}

	// Nếu phần định trị toàn bit không
	if (i != A.length() - 1)
	{
		// Nếu phần mũ toàn bit không thì là số 0
		if (checkE == 0)
		{
			return "0";
		}
		else if (checkE == 15) // Nếu phần mũ toàn bit một thì là số inf
		{
			if (A[0] == '0')
			{
				return "inf";
			}
			else
			{
				return "-inf";
			}
		}
	}
	else // Trường hợp này số không hợp lệ
	{
		if (checkE == 15)
		{
			return "NaN";
		}
	}

	// Phần dấu
	i = 0;
	if (A[0] == '1')
	{
		result += '-';
		i++;
	}
	// Phần mũ: là một số dương 15 bit
	// Khởi tạo số nguyên 4 byte
	expo = 0;
	// Đưa lần lượt các bit vào
	for (int j = 0; j < E; j++)
	{
		expo = expo | (1 << j)*(A[E - j] - 48);
	}
	// Được số dương
	// Trừ đi độ lệch được phần mũ
	expo -= BIAS;
	// Đưa các bit tiếp theo vao chuỗi nhị phân
	for (int j = E + 1; j < A.length(); j++)
	{
		B += A[j];
	}

	// Thêm bit một vào đầu chuỗi
	B = '1' + B;
	if (expo < 0)
	{
		for (int j = expo; j < -1; j++)
		{
			B = '0' + B;
		}
		B = "0." + B;
	}
	else
	{
		if (expo < 113)
		{
			B.insert(B.begin() + expo + 1, '.');
		}
		else
		{
			while (expo != B.length())
			{
				B += '0';
			}
			B += "0.0";
		}
	}

	// Lấy phần nguyên
	while (B[i] != '.')
	{
		s += B[i];
		i++;
	}
	// Chuyển sang thập phân
	result += binStringToDec(s);
	// Thêm dấu chấm vào kết quả
	result += '.';
	i++;
	// Lấy phần thập phân
	while (i < B.length())
	{
		p += B[i];
		i++;
	}
	// Độ dài
	int z = p.length();
	while (p[z] == '1')
	{
		z--;
	}

	// Chuyển phần thập phân sang số thập phân
	s = "0";
	temp = tenPowDec(z);
	temp2 = decDivTwoPow(temp, 1);
	for (i = 0; i < z; i++)
	{
		if (p[i] == '1')
		{
			for (int j = 0; j < temp2.length() - p.length(); j++)
			{
				temp2 = '0' + temp2;
			}
			s = decimalPlusDecimal(s, temp2);
		}
		temp2 = decDivTwoPow(temp2, 1);
	}
	result += s;
	return result;
}

// Hàm nhập
void QFloat::ScanQFloat(int base)
{
	int i;
	string nhap;
	getline(cin, nhap);
	if (nhap == "")
	{
		return;
	}
	// Nếu nhập vào ở dạng thập phân chuyển sang nhị phân
	if (base == 10)
	{
		nhap = decToBin_q(nhap);
	}
	// Đưa vào lưu trữ
	for (i = 0; i < nhap.length(); i++)
	{
		number[(MAX - 1 - i) / 32] = number[(MAX - 1 - i) / 32] | (nhap[nhap.length() - i - 1] - 48)*(1 << (i) % 32);
	}
}

// Hàm xuất
void QFloat::PrintQFloat(int base)
{
	int i;
	int bit;
	string xuat;
	// Chuyển các bit vào chuỗi nhị phân
	for (i = 0; i < MAX; i++)
	{
		bit = (number[i / 32] >> ((MAX - 1 - i) % 32)) & 1;
		xuat += (char)(bit + 48);
	}
	// Nếu yêu cầu in ra thập phân chuyển sang dạng thập phân
	if (base == 10)
	{
		xuat = binToDec_q(xuat);
	}
	cout << xuat;
}
