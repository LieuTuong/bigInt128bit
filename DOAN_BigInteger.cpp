
#include "pch.h"
#include <iostream>
#include<string>
#include<bitset>
#include<array>

using namespace std;
#define MAX 128

typedef struct
{
	uint32_t data[4];
}QInt;


void xuat(array<int,MAX>a)
{
	for (auto& x : a)
	{
		cout << x;
	}
	cout << endl;
}
//ham khoi tao tat ca cac gia tri trong struct data = 0, nghia la cho tat ca cac bit trong mang la 0
void initQInt(QInt& x)
{
	for (uint32_t i = 0; i < 4; i++)
		x.data[i] = 0;
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
array<int,MAX> bu1(array<int,MAX> a)
{
	array<int,MAX> tmp;
	for (int i = 0; i < MAX; i++)
	{
		tmp[i] = (a[i] == 1) ? 0 : 1;
	}
	return tmp;
}



//Ham lay bu 2
array<int,MAX> bu2(array<int, MAX> a)
{
	a = bu1(a);
	int soDu = 1;
	array<int, MAX> bu2 = { 0 };
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



//Ham chuyen tu QInt sang mang int a[MAX]
array<int, MAX> QInt_To_Arr(const QInt& number)
{
	array<int, MAX> a = { 0 };
	for (int i = 0; i < MAX; i++)
	{
		if ((number.data[i / 32] >> (32 - 1 - i % 32)) & 1 == 1)
		{
			a[i] = 1;
		}
	}
	return a;
}



//Ham chuyen tu mang a sang Qint
QInt Arr_To_QInt(const array<int, MAX>& binArr)
{
	QInt number;
	initQInt(number);
	for (int i = 0; i < MAX; i++)
	{
		if (binArr[i] == 1)
		{
			number.data[i / 32] = number.data[i / 32] | (1 << (32 - 1 - i % 32));
		}
	}
	return number;
}



//Ham dao nguoc mang (sau khi chia 2 thi he nhi phan la lay so du tu duoi len)
array<int, MAX> reverse(array<int, MAX>a)
{
	array<int, MAX> rev_arr = { 0 };
	for (int i = 0; i < MAX; i++)
	{
		rev_arr[i] = a[MAX - i - 1];
	}
	return rev_arr;
}



//ham chuyen tu thap phan sang nhi phan
array<int, MAX> DecToBin(string userInputStr)
{	
	array<int, MAX> binary = { 0 };

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
	array<int, MAX> res=reverse(binary);

	if (IsSigned)
	{
		res = bu2(res);
	}
	return res;
	
}


//Ham nhap so QInt, con thieu cai doc File, ko biet cho 2 tham so co dc ko
void ScanQInt(QInt &number,string userInputStr)
{
	initQInt(number);
	
	array<int, MAX> binArr = DecToBin(userInputStr);
	
	number = Arr_To_QInt(binArr);

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



// cho do dai 2 chuoi bang nhau de cong 2 chuoi lai
void canBang2Chuoi( string& a,  string& b)
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



string operator+( string& a, string& b)
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
	array<int, MAX> a = QInt_To_Arr(number);

	//Tu mang nhi phan a chuyen sang so thap phan
	string decNum;
	string tmp;
	for (int i = 0; i < MAX; i++)
	{
		if (a[i] == 1)
		{
			tmp = _2_mu_n(MAX - 1 - i);
			decNum = decNum +  tmp;
		}
	}
	cout << "\nSo chuyen sang he thap phan: ";
	cout << decNum;
}





//Tim vi tri bit 1 trong day tinh tu vi tri dang xet
int viTriBit1(array<int, MAX> a,int viTriDangXet = 0)
{
	int i = (viTriDangXet == 0) ? viTriDangXet : viTriDangXet + 1;

	for (i ; i < MAX; i++)
	{
		if (a[i] == 1)
		{
			return i;
		}
	}
	return -1;
}



bool operator < (const QInt& a, const QInt& b)
{
	
	//chuyen QInt qua mang de so sanh
	array<int, MAX> A = QInt_To_Arr(a);
	array<int, MAX> B = QInt_To_Arr(b);
	

	// tim vi tri bit 1 dau tien
	int bit1_A = viTriBit1(A);
	int bit1_B = viTriBit1(B);

	while (1)
	{
		if (bit1_A > bit1_B)//vi tri bit 1 cua a > vi tri bit 1 dau tien cua b
			return true;
		else if (bit1_A < bit1_B)
			return false;	
		else if (bit1_A == bit1_B)
		{
			bit1_A = viTriBit1(A, bit1_A);
			bit1_B = viTriBit1(B, bit1_B);
		}
	}
}



bool operator > (const QInt& a, const QInt& b)
{
	return !(a < b);
}




bool operator == (const QInt& a, const QInt& b)
{
	bool flag=true;

	//chuyen QInt qua mang de so sanh
	array<int, MAX> A = QInt_To_Arr(a);
	array<int, MAX> B = QInt_To_Arr(b);

	for (int i = 0; i < MAX; i++)
	{
		if (A[i] != B[i])
		{
			flag = false;
			break;
		}
	}
	return flag;
}


bool operator <= (const QInt& a, const QInt& b)
{
	if (a < b || a == b)
		return true;
	return false;
}



bool operator >= (const QInt& a, const QInt& b)
{
	return !(a <= b);
}



QInt operator & (const QInt& a, const QInt& b)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = a.data[i] & b.data[i];
	}
	return res;
}


//QInt operator & (const QInt& a, const int& b)
//{
//
//}

QInt operator | (const QInt& a, const QInt& b)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = a.data[i] | b.data[i];
	}
	return res;
}



QInt operator ^ (const QInt& a, const QInt& b)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = a.data[i] ^ b.data[i];
	}
	return res;
}



QInt operator ~ (const QInt& a)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = ~a.data[i];
	}
	return res;
}


 // Neu so luong bit dixh < 0 thi xu li nhu the nao, cho i kien???????
QInt operator >> ( const QInt& a, int bit)
{
	array<int, MAX> A = QInt_To_Arr(a);
	
	if (bit >= MAX) //neu dich so luong bit nhieu hon 128, thi toan bi mang se = 0
	{
		A = { 0 };
	}
	else
	{
		for ( int i = MAX-1; i >=0; i--)
		{
			A[i] = (i - bit) < 0 ? 0 : A[i - bit];
		}		 
	}
	return  Arr_To_QInt(A);
}



// thieu truong hop bit < 0
QInt operator << (const QInt& a,  int bit)
{
	
	array<int, MAX> A = QInt_To_Arr(a);

	if (bit >= MAX) //neu dich so luong bit nhieu hon 128, thi toan bi mang se = 0
	{
		A = { 0 };
	}
	else
	{
		for (int i = 0; i < MAX; i++)
		{
			A[i] = (i + bit) > (MAX - 1) ? 0 : A[i + bit];
		}
	}
	return  Arr_To_QInt(A);	
}




QInt rol(const QInt& a)
{
	array<int, MAX> A = QInt_To_Arr(a);
	
	int MSB = A[0];// giu bit trai nhat 
	for (int i = 0; i < MAX - 1; i++)
	{
		A[i] = A[i + 1];
	}
	A[MAX - 1] = MSB;// bit trai nhat thanh bit phai nhat
	return  Arr_To_QInt(A);	
}



QInt ror(const QInt& a)
{
	array<int, MAX> A = QInt_To_Arr(a);

	int LSB = A[MAX - 1];
	for (int i = MAX - 1; i > 0; i--)
	{
		A[i] = A[i - 1];
	}
	A[0] = LSB;
	return Arr_To_QInt(A);
}


int main()
{
	string ss = "1234458734329";
	string s = "19";
	string s2 = "30";
	array<int, MAX> res = DecToBin(s);
	
    QInt a;
	ScanQInt(a,s);
	//PrintQInt(a);
	

	//QInt b;
	//ScanQInt(b, s);
	////PrintQInt(b);
	//

	QInt d = rol(a);
	cout << "\nrol<<" << endl;
	PrintQInt(d);
	
	system("pause");
	return 0;
}


