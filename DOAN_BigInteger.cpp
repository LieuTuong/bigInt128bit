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


int main()
{
	string ss = "1234458734329";
	string s = "-123";
	int* res = DecToBin(s);
	xuat(res);
	/*QInt number;
	ScanQInt(number,s);*/
	
	system("pause");
	return 0;
}


