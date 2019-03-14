
#include "pch.h"
#include <iostream>
#include<string>
#include<bitset>
#include<array>

using namespace std;
#define MAX 128

// do ko chac unsigned int luon la 4 bytes, nen dung unit32_t
typedef struct
{
	uint32_t data[4];
	bool IsSigned;
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

string remove0(const string& number)
{
	string res = number;
	for (int i = 0; i < number.length(); i++)
	{
		if (number[i] != '0')//Vi tri khac 0 dau tien
		{
			res.erase(0, i);
			break;
		}
	}
	return res;
}


//ten ham da bieu thi tat ca:))
string chia2(string bigInt)
{
	
	string tmp;
	string soChia = remove0(bigInt);

	unsigned short int i = 0, j = 0, k = 0;
	tmp.resize(bigInt.length());
	if (stringToNum(soChia[0]) < 2)
	{
		i = 1; 
		j = 10;
	}
	for (; i < soChia.length(); i++)
	{
		tmp[k++] = ((soChia[i] - '0' + j) / 2 + '0');
		j = ((soChia[i] - 48 + j) % 2) * 10;
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



//
//string nhan2(string bigInt)
//{
//	string res = "";
//	 int len = bigInt.length();
//	int tmp = 0;
//
//	for ( int i = len-1; i>=0 ; i--)
//	{
//		tmp = stringToNum(bigInt[i]) * 2 + tmp ;
//		res.insert(0, 1, numToString(tmp%10));//lay phan don vi cho vao string
//		tmp = tmp / 10;// lay phan chuc de tinh tiep
//	}
//	if (tmp > 0)  // Neu khac 0 thi bo them vao chuoi res
//	{
//		res.insert(0, 1, numToString(tmp));
//	}
//	return res;
//}

int soSanhVoi1(const string& a)
{
	int viTriDauCham=0;
	for (viTriDauCham; viTriDauCham < a.length(); viTriDauCham++)
	{
		if (a[viTriDauCham] == '.')
			break;
	}
	string phanNguyen = "";
	for (int i = 0; i < viTriDauCham; i++)
		phanNguyen.push_back(a[i]);

	string phanThapPhan = "";
	for (int i = viTriDauCham + 1; i < a.length(); i++)
		phanThapPhan.push_back(a[i]);

	if (phanNguyen.compare("1") < 0)
		return -1;
	else
	{
		if (phanNguyen.compare("1") == 0)
		{
			int len = phanThapPhan.length();
			string _0(len, '0');
			if (phanThapPhan.compare(_0) == 0)return 0;
			else return 1;
		}
	}
}
string operator * (string bigNumber, int x)
{
	string res = "";
	int len = bigNumber.length();
	int tmp = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		if (bigNumber[i] == '.')
		{
			res.insert(0, 1, '.');
		}
		else 
		{
			tmp = stringToNum(bigNumber[i]) * x + tmp;
			res.insert(0, 1, numToString(tmp % 10));//lay phan don vi cho vao string
			tmp = tmp / 10;// lay phan chuc de tinh tiep
		}
		
	}
	if (tmp > 0)  // Neu khac 0 thi bo them vao chuoi res
	{
		res.insert(0, 1, numToString(tmp));
	}
	return res;
}
//string _2_mu_n (int n)
//{
//	string res = "1";
//	for (int i = 1; i <= n; i++)
//	{
//		res = nhan2(res);
//	}
//	return res;
//
//}

string _x_mu_n(int coSo, int soMu)
{
	string res = "1";
	for (int i = 1; i <= soMu; i++)
	{
		res = res*coSo;
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


//Ham cong 2 chuoi bigInt
string operator + (string& a,string& b)
{
	string res = "";
	canBang2Chuoi(a, b);
	int len = a.length();

	int tmp = 0;
	for (int i = len - 1; i >= 0; --i)
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


//Ham tru 2 chuoi BigInt
string operator - (string& soTru, string& soBiTru)
{
	string res = "";
	canBang2Chuoi(soTru, soBiTru);

	int len = soTru.length();
	int tmp = 0;// soNho
	int hieu;
	for (int i = len - 1; i >= 0; --i)
	{
		
		if (soTru[i] < soBiTru[i]) //Neu tai vi tri dg xet, (soBiTru < soTru ) lay (soBiTru + 10 ) - soBiTru
		{
			hieu = (stringToNum(soTru[i]) + 10) - stringToNum(soBiTru[i]) - tmp;
			tmp = 1;
		}
		else// neu soBiTru lon hon thi lay (SoBiTru - soTru)
		{
			hieu=stringToNum(soTru[i]) - stringToNum(soBiTru[i]) - tmp;			
		}
		res.insert(0, 1, numToString(hieu));// bo ket qua tinh dc theo hang vao chuoi res
	}
	return res;
}
//
//string operator * (string& a, string& b)
//{
//	string res;
//	for (int i = 0; i < a.length(); i++)
//	{
//		string tmpStr;
//		int soDu = 0, tmp;
//		for (int j = 0; j < b.length(); j++)
//		{
//			tmp = a[i] * b[j] + soDu;
//			tmpStr.push_back(tmp % 10);
//			soDu = tmp / 10;
//		}
//		if (soDu > 0)
//		{
//			tmpStr.push_back(soDu);
//		}
//		for (int j = 0; j < i; j++)
//		{
//			tmpStr.insert(res.begin(), 0);
//		}
//		res = res + tmpStr;
//	}
//	return res;
//}

// Ham chuyen tu nhi phan sang thap phan
string BinToDec(array<int,MAX> bit)
{
	string decNum, tmp;
	for (int i = 0; i < MAX; i++)
	{
		if (bit[i] == 1)
		{
			tmp = _x_mu_n(2,MAX - 1 - i);
			decNum = decNum + tmp;
		}
	}
	return decNum;
}


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
			tmp = _x_mu_n(2,MAX - 1 - i);
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
		int tmp;
		tmp = (a.IsSigned) ? 1 : 0;
		for ( int i = MAX-1; i >=0; i--)
		{
			A[i] = (i - bit) < 0 ? tmp : A[i - bit];
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

string operator * (string &a, string& b)
{
	string resStr;
	int* res = new int[a.length() + b.length()];
	for (int i = 0; i < a.length() + b.length(); i++)
		res[i] = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		for (int j = b.length() - 1; j >= 0; j--)
		{
			res[1 + i + j] += (a[i] - '0')*(b[j] - '0');
		}
	}

	for (int i = a.length() + b.length(); i >= 0; i--)
	{
		if (res[i] > 9)
		{
			res[i - 1] += res[i] / 10;
			res[i] %= 10;
		}
	}
	for (int i = 0; i < a.length() + b.length(); i++)
	{
		resStr += (res[i] + '0');
	}
	return resStr;
}

typedef struct
{
	uint32_t data[4];
}Qfloat;


array<int, MAX> operator + (const array<int, MAX>& A, const array<int, MAX>& B)
{
	array<int, MAX> res;
	int tmp = 0;
	for (int i = MAX - 1; i >= 0; i--)
	{
		tmp = A[i] + B[i] + tmp;
		if (tmp == 2)
		{
			res[i] = 0;
			tmp = 1;
		}
		else if (tmp == 3)
		{
			res[i] = 1;
			tmp = 1;
		}
		else
		{
			res[i] = tmp;
			tmp = 0;
		}
	}
	return res;
}
//Cong 2 QINt
QInt operator + (const QInt& a, const QInt& b)
{
	array<int, MAX> A = QInt_To_Arr(a);
	array<int, MAX> B = QInt_To_Arr(b);
	array<int, MAX> res;
	res = A + B;
	return Arr_To_QInt(res);
}

/*Phep tru 2 QInt a va b
   a-b=a+(-b)
   a + soBu2(b)
   */
QInt operator - (const QInt& soTru, const QInt& soBiTru)
{
	array<int, MAX> SoTru = QInt_To_Arr(soTru);
	array<int, MAX> SoBiTru = QInt_To_Arr(soBiTru);
	array<int, MAX> res;

	//So bu 2 cua so bi tru
	SoBiTru = bu2(SoBiTru);

	res = SoTru + SoBiTru;
	cout << "\nPhan nhi phan sau khi tru: " << endl;
	xuat(res);
	return Arr_To_QInt(res);
}


QInt operator * (const QInt& a, const QInt& b)
{

}
/*Giai thich thuat toan chuyen phan thap phan cua Qfloat sang he nhi phan
VD: so 12.75, phan thap phan = 0.75
Neu tinh theo cong thuc thi: 0.75 * 2 = 1.5 => 1
						 (1.5 - 1)* 2 = 1   => 1
vi co dau cham kho tinh toan, nen chuyen sang the nay: 0.75 * 10^2 * 2 = 150 > 10^2 => 1
													  (150 - 10^2) * 2 = 100 = 10^2 => 1
Noi chung la chuyen sang so nguyen cho de tinh:)))
*/
string DecToBin_PhanThapPhan(string phanThapPhan)
{
	string bin="";
	
	while (1)
	{
		phanThapPhan = phanThapPhan * 2;
		if (soSanhVoi1(phanThapPhan)==0)
		{
			bin.push_back('1');
			break;
		}
		else if (soSanhVoi1(phanThapPhan) > 0)
		{
			bin.push_back('1');
			for (int i = 0; i < phanThapPhan.length(); i++)
			{
				if (phanThapPhan[i] == '.')
				{
					phanThapPhan[i - 1] = '0';
					break;
				}
			}
		}
		else if (soSanhVoi1(phanThapPhan) < 0)
		{
			bin.push_back('0');
		}
		
	}
	return bin;
}


void ScanQfloat(Qfloat &x, string userInputStr)
{

}
int main()
{
	/*string ss = "1234458734329";
	string s = "19";
	string s2 = "30";
	array<int, MAX> res = DecToBin(s);
	
    QInt a;
	ScanQInt(a,s);*/
	//PrintQInt(a);
	

	//QInt b;
	//ScanQInt(b, s);
	////PrintQInt(b);
	//

	string a = "69";
	string b = "79";
	QInt aa,bb;
	ScanQInt(aa, a);
	ScanQInt(bb, b);
	QInt res = aa - bb;
	cout << "\nPhep cong: " << endl;
	PrintQInt(res);
	return 0;
}

