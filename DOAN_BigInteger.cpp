// DOAN_BigInteger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<string>
#include<bitset>

using namespace std;
#define MAX 128
typedef struct
{
	uint32_t data[4];
}QInt;
void xuat(int*a)
{
	for (int i = 0; i < MAX; i++)
	{
		cout << a[i];
	}
	cout << endl;
}

int stringToNum(char c)     // chuyen char sang so
{
	return c - '0';
}

char numToString(int n)     // chuyen so sang char
{
	return (char)(n + 48);
}
//ten ham da bieu thi tat ca:))
string chia2(string bigInt)
{
	
	string tmp;
	unsigned short int i = 0, j = 0, k = 0;
	tmp.resize(bigInt.length());
	if (bigInt[0] - '0' < 2)
	{
		i = 1; 
		j = 10;
	}
	for (; i < bigInt.length(); i++)
	{
		tmp[k++] = ((bigInt[i] - '0' + j) / 2 + '0');
		j = ((bigInt[i] - 48 + j) % 2) * 10;
	}
	tmp.resize(k);
	return tmp;
}
// Ham lay bu 1
int* bu1(int* a)
{
	static int tmp[MAX];
	for (int i = 0; i < MAX; i++)
	{
		tmp[i] = (a[i] == 1) ? 0 : 1;
	}
	return tmp;
}



//Ham lay bu 2
int* bu2(int* a)
{
	a = bu1(a);
	int soDu = 1;
	static int bu2[MAX] = { 0 };
	for (int i = MAX - 1; i >= 0; i--)
	{
		if (a[i] == 0 && soDu == 1)
		{
			bu2[i] = 1;
			soDu = 0;
		}
		else if (a[i] == 1 && soDu == 0)
		{
			bu2[i] = 1;
		}
	}
	
	return bu2;
}



//Ham dao nguoc mang (sau khi chia 2 thi he nhi phan la lay so du tu duoi len)
int* reverse(int *a)
{
	static int rev_arr[MAX] = { 0 };
	for (int i = 0; i < MAX; i++)
	{
		rev_arr[i] = a[MAX - i - 1];
	}
	return rev_arr;
}

//ham chuyen tu thap phan sang nhi phan
int* DecToBin(string userInputStr)
{	
    int binary[MAX] = { 0 };

	bool IsSigned = false;
	if (userInputStr[0] == '-')
	{
		IsSigned = true;
		userInputStr.erase(0, 1);
	}
	
	for (unsigned short int i = 0; userInputStr.length()!=0; i++)
	{
		if ((userInputStr[userInputStr.length() - 1] - 48) % 2 != 0) {
			binary[i] = 1;
			userInputStr[userInputStr.length() - 1] -= 1;
		}
		else binary[i] = 0;
		userInputStr = chia2(userInputStr);
	}
	int* res=reverse(binary);

	if (IsSigned)
	{
		res = bu2(res);
	}
	return res;
	
}
//ham khoi tao tat ca cac gia tri trong struct data = 0, nghia la cho tat ca cac bit trong mang la 0
void initQInt(QInt& x)
{
	for (uint32_t i = 0; i < 4; i++)
		x.data[i] = 0;	
}

//Ham nhap so QInt, con thieu cai doc File, ko biet cho 2 tham so co dc ko
void ScanQInt(QInt &number,string userInputStr)
{
	initQInt(number);
	
	int* binArr = DecToBin(userInputStr);
	
	for (int i = 0; i < MAX; i++)
	{
		if (binArr[i] == 1)
		{
			number.data[i / 32] = number.data[i / 32] | (1 << ( 32-1-i % 32));
		}
	}
	cout << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << bitset<32>(number.data[i]);
	}
	
}


string nhan2(string bigInt)
{
	string res = "";
	 int len = bigInt.length();
	int tmp = 0;

	for ( int i = len-1; i>=0 ; i--)
	{
		tmp = stringToNum(bigInt[i]) * 2 + tmp ;
		res.insert(0, 1, numToString(tmp%10));//lay phan don vi cho vao string
		tmp = tmp / 10;// lay phan chuc de tinh tiep
	}
	if (tmp > 0)  // Neu khac 0 thi bo them vao chuoi res
	{
		res.insert(0, 1, numToString(tmp));
	}
	return res;
}

string _2_mu_n (int n)
{
	string res = "1";
	for (int i = 1; i <= n; i++)
	{
		res = nhan2(res);
	}
	return res;

}

void canBang2Chuoi(string& a, string& b)// cho do dai 2 chuoi bang nhau de cong 2 chuoi lai
{
	int a_len = a.length(), b_len = b.length();
	if (a_len > b_len)
	{
		b.insert(0, a_len - b_len, '0');
	}
	else
	{
		a.insert(0, b_len - a_len, '0');
	}
}


string operator+(string& a,string& b)
{
	string res = "";
	canBang2Chuoi(a, b);
	int len = a.length();

	int tmp = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		tmp = stringToNum(a[i]) + stringToNum(b[i]) + tmp;
		res.insert(0, 1, numToString(tmp % 10));
		tmp /= 10;
	}
	if (tmp > 0)
	{
		res.insert(0, 1, numToString(tmp));
	}
	return res;
}
// Ham chuyen tu he nhi phan sang he thap phan


//ham xuat so QInt, xuat ra so he thap phan
void PrintQInt(QInt number)
{
	//chuyen tu QInt sang mang a
	int a[MAX] = { 0 };
	for (int i = 0; i < MAX; i++)
	{
		if ((number.data[i / 32] >> (32 - 1 - i % 32)) & 1 == 1)
		{
			a[i] = 1;
		}
	}
	

	//Tu mang nhi phan a chuyen sang so thap phan
	string decNum = "0";
	for (int i = 0; i < MAX; i++)
	{
		if (a[i] == 1)
		{
			decNum = decNum + _2_mu_n(MAX - 1 - i);
		}
	}
	cout << "\nSo chuyen sang he thap phan: ";
	cout << decNum;
}

int main()
{
	/*string ss = "1234458734329";
	string s = "15";
	int* res = DecToBin(s);
	
	QInt number;
	ScanQInt(number,s);
	

	PrintQInt(number);*/

	
	return 0;
}


