#include <iostream>
#include "Qint.h"
#include "QFloat.h"
#include <algorithm>
using namespace std;


//BASE		t1				t2					t3
//base		base			num_str
//base		~,ror,rol		num_str
//base		num_str			<<,>>				offset
//base		num_str			+,-,*,/,&,|,^		num_str

int main(int argc, char *argv[])
{
	if (strcmp(argv[3], "1") == 0)
	{
		ifstream infile(argv[1]);
		ofstream outfile(argv[2]);
		//ifstream infile("input.txt");
		//ofstream outfile("output1.txt");
		//

		int base;
		string t1, t2, t3;

		infile.seekg(ios::beg);
		while (infile >> base >> t1 >> t2)
		{
			Qint q, q1, q2;
			bool Printed = false;

			if (t1 == "2" || t1 == "10" || t1 == "16" || t1 == "~" || t1 == "ror" || t1 == "rol")
			{
				Scan(q, t2, base);

				if (t1 == "2" || t1 == "10" || t1 == "16")
				{
					Print(outfile, q, atoi(t1.c_str()));
					Printed = true;
				}
				else
				{
					if (t1 == "~")
						q = ~q;
					else if (t1 == "ror")
						q = q.RotateRight(q, 1);
					else
						q = q.RotateLeft(q, 1);
				}
			}
			else
			{
				infile >> t3;

				if (t2 == ">>")
				{
					Scan(q1, t1, base);
					q = q1 >> atoi(t3.c_str());
				}
				else if (t2 == "<<")
				{
					Scan(q1, t1, base);
					q = q1 << atoi(t3.c_str());
				}
				else
				{
					Scan(q1, t1, base);
					Scan(q2, t3, base);

					switch (t2[0])
					{
					case '+':
						q = q1 + q2;
						break;
					case '-':
						q = q1 - q2;
						break;
					case '*':
						q = q1 * q2;
						break;
					case '/':
						q = q1 / q2;
						break;
					case '&':
						q = q1 & q2;
						break;
					case '|':
						q = q1 | q2;
						break;
					case'^':
						q = q1 ^ q2;
						break;
					default:
						break;
					}
				}
			}

			if (Printed == false)
				Print(outfile, q, base);

			if (infile.eof())
				break;
			else
				outfile << endl;
		}

		infile.close();
		outfile.close();
	}
	if (strcmp(argv[3], "2") == 0)
	{
		int a;
		int b;
		FILE* in;
		FILE* out;
		freopen_s(&in, *(argv + 1), "r", stdin);
		while (!feof(in))
		{
			// Nhập vào
			cin >> a;
			if (a == 0)
			{
				break;
			}
			//cin.get();
			cin >> b;
			cin.get();
			QFloat* A = new QFloat;
			A->ScanQFloat(a);

			// Xuất ra
			freopen_s(&out, *(argv + 2), "a", stdout);
			A->PrintQFloat(b);
			cout << endl;
			a = 0;
		}
	}
	return 0;
}
