#include <fstream>
#include <iostream> 
#include <iomanip> 
#include <string> 
#include <cmath>
#include <ctime>
using namespace std;

void RandomMistake(char* buffer1,long size1,double percent)
{
	srand(time(NULL));
	int byte;
	int bit;
	int SetOrDelete;
	int PowerOf2;

	for (int i = 0; i < floor(size1*percent); i++)
	{
		byte = rand() % (size1+1);
		//cout << "bajt  " << byte << endl;
		bit = rand() % (8);
		//cout << "bit  " << bit << endl;

		PowerOf2 = pow(2, bit);
		SetOrDelete = ((PowerOf2 & buffer1[byte]) ? 0 : 1);
		//cout << "SetOrDelete  " << SetOrDelete << endl;

		if (SetOrDelete)
		{
			//set bit
			buffer1[byte] = (buffer1[byte])| (PowerOf2);
		}
		else
		{
			//delete bit
			buffer1[byte] = (buffer1[byte]) & (~PowerOf2);
		}
	}
	cout << "Wykonano bledy" << endl;
}
bool WasValueDrawn(int iLiczba, int* tab, int ile, int *tab1,int bit1)
{
	if (ile <= 0)
		return false;

	int i = 0;
	do
	{
		if (tab[i] == iLiczba)
		{
			if (tab1[i]==bit1)
			return true;
		}

		i++;
	} while (i < ile);

	return false;
}
void RandomMistakeWithoutRepetition(char* buffer3, long size3, double percent3)
{
	srand(time(NULL));
	int byte;
	int bit;
	int SetOrDelete;
	int PowerOf2;
	int* RandMemoryByte = new int[floor(size3*percent3)];
	int* RandMemoryBit = new int[floor(size3*percent3)];
	int which=0;
	
	cout << "Rozpoczynam dodawanie bledow, ta funkcja moze troche potrwac dla duzych plikow\n";
	cout << "...";
	for (int i = 0; i < floor(size3*percent3); i++)
	{
		do
		{
			byte = rand()%(size3+1);
			RandMemoryByte[i] = byte;
			//cout << "bajt  " << byte << endl;
			bit = rand()%(8);
			RandMemoryBit[i] = bit;
			//cout << "bit  " << bit << endl;
			//cout << i << " \n";
		} while ( WasValueDrawn(byte, RandMemoryByte,i,RandMemoryBit,bit) );

		PowerOf2 = pow(2, bit);
		SetOrDelete = ((PowerOf2 & buffer3[byte]) ? 0 : 1);
		//cout << "SetOrDelete  " << SetOrDelete << endl;

		if (SetOrDelete)
		{
			//set bit
			buffer3[byte] = (buffer3[byte]) | (PowerOf2);
		}
		else
		{
			//delete bit
			buffer3[byte] = (buffer3[byte]) & (~PowerOf2);
		}
	}
	cout << "Wykonano bledy" << endl;
	delete[] RandMemoryBit;
	delete[] RandMemoryByte;
}
void CountParityBit(char *buffer2,long size2)
{
	unsigned int v;
	bool parity = false;

	for (int i = 0; i < size2; i++)
	{
		v = (int)(unsigned char)(buffer2[i]);
		//cout << (int)(unsigned char)(buffer[i]) << " "; //bytes in decimal

		for (int m = 0x80; m; m >>= 1)
		{
			//cout << ((v & m) ? 1 : 0);
			if ((v&m))
			{
				if (parity)
					parity = false;
				else
					parity = true;
			}
		}
		//cout << " ";
		//outfile<<(buffer[i]);
		//add parity bit
		if (i == size2 - 1)
		{
			buffer2[i + 1] = parity ? '1' : '0';
		}
	}
	//cout << parity << "  ";
	cout << "Bit parzystosci obliczony : " <<parity<< endl;
}
void SumModulo (char *buffer2, long size2, int mod , ofstream & Myfile)
{
	unsigned int v;
	int SumOfModulo=0;
	//int SumOfModulo2 = 0;

for (int i = 0; i < size2; i++)
{
	v = (int)(unsigned char)(buffer2[i]);
	//cout << (int)(unsigned char)(buffer[i]) << " "; //bytes in decimal

	SumOfModulo = (SumOfModulo + v) % mod;
	//SumOfModulo2 = SumOfModulo2%mod + v % mod;

	//cout << " ";
	//outfile<<(buffer[i]);
	if (i == size2 - 1)
	{
		Myfile << SumOfModulo;
	}
}
cout << "Suma modulo obliczona : " << SumOfModulo << endl;
//cout << "Suma modulo obliczona : " << SumOfModulo2 % mod << endl;
}
void CRC(char* buffer2, long size2, int divlen, ofstream & Myfile1, ofstream & Myfile2, bool WhichMistake,double percent)
{
	int i, k;
	long long size3 = size2 * 8;
	long long j = 0;

	int* message = new int[size3+divlen-1];
	unsigned int v;


	for (int i = 0; i < size2; i++)
	{
		v = (int)(unsigned char)(buffer2[i]);
		//cout << (int)(unsigned char)(buffer[i]) << " "; //bytes in decimal

		for (int m = 0x80 ; m; m >>= 1)
		{
			//cout << ((v & m) ? 1 : 0);
			if ((v&m))
				message[j] = 1;
			else
				message[j] = 0;
			j++;
		}
	}

	int* g = new int[divlen];

	cout << "\n Wprowadz Generator:";
	for (i = 0; i<divlen; i++)
	{
		cin >> g[i];
	}
	
	/*for (i = 0; i<size3; i++)
	{
		cout << message[i];
	}*/
	cout << "\n Generator :";
	for (i = 0; i<divlen; i++)
	{
		cout << g[i];
	}
	

	int rs = divlen - 1;
	cout << "\n Tyle zer dodajemy: " << rs;
	
		for (i = size3; i < size3 + rs; i++)
		{
			message[i] = 0;
		}
	
	int* temp = new int[size3+rs];
	for (i = 0; i<size3 + rs; i++)
	{
		temp[i] = message[i];
	}

	/*cout << "\n Wiadomosc po dodaniu zer 0's :";
	for (i = 0; i<size3 + rs; i++)
	{
		cout << temp[i];
	}*/
	
	for (i = 0; i<size3; i++)
	{
		j = 0;
		k = i;

		if (temp[k] >= g[j])
		{
			for (j = 0, k = i; j<divlen; j++, k++)
			{
				if ((temp[k] == 1 && g[j] == 1) || (temp[k] == 0 && g[j] == 0))
				{
					temp[k] = 0;
				}
				else
				{
					temp[k] = 1;
				}
			}
		}
	}

	int* crc = new int[rs];
	for (i = 0, j = size3; i<rs; i++, j++)
	{
		crc[i] = temp[j];
	}

	cout << "\n Obliczono  CRC, zapisano do pliku ";
	for (i = 0; i<rs; i++)
	{
		cout << crc[i];
		Myfile1 << crc[i];
	}
	//cout << "CRC zapisano do pliku\n";
	cout << endl;
	
	//------------------------------------------------------------------------------
	cout << "Przeczytano nowy plik\n";
	if (!WhichMistake)
		RandomMistake(buffer2, size2, percent);
	else RandomMistakeWithoutRepetition(buffer2, size2, percent);

	Myfile2.write(buffer2, size2);

	j = 0;
	for (int i = 0; i < size2; i++)
	{
		v = (int)(unsigned char)(buffer2[i]);
		//cout << (int)(unsigned char)(buffer[i]) << " "; //bytes in decimal

		for (int m = 0x80; m; m >>= 1)
		{
			//cout << ((v & m) ? 1 : 0);
			if ((v&m))
				message[j] = 1;
			else
				message[j] = 0;
			j++;
		}
	}

	cout << "\n Tyle miejsc dodamy do wiadomosci: " << rs;

	for (i = size3; i < size3 + rs; i++)
	{
		message[i] = temp[i];
	}

	for (i = 0; i<size3 + rs; i++)
	{
		temp[i] = message[i];
	}

	/*cout << "\n Wiadomosc po dodaniu :";
	for (i = 0; i<size3 + rs; i++)
	{
		//cout << temp[i];
	}*/

	for (i = 0; i<size3; i++)
	{
		j = 0;
		k = i;

		if (temp[k] >= g[j])
		{
			for (j = 0, k = i; j<divlen; j++, k++)
			{
				if ((temp[k] == 1 && g[j] == 1) || (temp[k] == 0 && g[j] == 0))
				{
					temp[k] = 0;
				}
				else
				{
					temp[k] = 1;
				}
			}
		}
	}

	for (i = 0, j = size3; i<rs; i++, j++)
	{
		crc[i] = temp[j];
	}

	cout << "\n Obliczony CRC: ";
	for (i = 0; i<rs; i++)
	{
		cout << crc[i];
		Myfile2 << crc[i];
	}
	//cout << "CRC zapisano do pliku\n";
	cout << endl;

	delete[] message;
	delete[] g;
	delete[] crc;
}

void MakeFile(int option, double percent1, int len)
{
	ifstream infile("hubi5.jpg", ifstream::binary);
	ofstream outfile("new.txt", ofstream::binary);

	// get size of file
	infile.seekg(0, infile.end);
	long size = infile.tellg();
	infile.seekg(0);

	// allocate memory for file content
	char* buffer = new char[size + 2];

	// read content of infile
	infile.read(buffer, size);
	cout << "Przeczytano plik" << endl;

	ifstream infile2("new.txt", ifstream::binary);
	ofstream outfile2("new2.txt", ofstream::binary);


	if (option == 0)
	{
		CountParityBit(buffer, size);
		outfile.write(buffer, size + 1);
		cout << "Zapisano bufor do pliku, bit parzystosci na koncu " << endl;
		infile2.read(buffer, size + 1);
		cout << "Przeczytano nowy plik" << endl;
		RandomMistake(buffer, size + 1, percent1);
		CountParityBit(buffer, size + 1);
		outfile2.write(buffer, size + 2);
		cout << "Zapisano dane z bledami do innego pliku,  bit parzystosci na koncu " << endl;
	}

	if (option == 1)
	{
		CountParityBit(buffer, size);
		outfile.write(buffer, size + 1);
		cout << "Zapisano bufor do pliku, bit parzystosci na koncu " << endl;
		infile2.read(buffer, size + 1);
		cout << "Przeczytano nowy plik" << endl;
		RandomMistakeWithoutRepetition(buffer, size + 1, percent1);
		CountParityBit(buffer, size + 1);
		outfile2.write(buffer, size + 2);
		cout << "Zapisano dane z bledami do innego pliku,  bit parzystosci na koncu " << endl;
	}

	if (option == 2)
	{
		outfile.write(buffer, size);
		SumModulo(buffer, size,256 ,outfile);
		cout << "Zapisano bufor do pliku, suma modulo na koncu " << endl;
		infile2.read(buffer, size);
		cout << "Przeczytano nowy plik" << endl;
		RandomMistake(buffer, size, percent1);
		outfile2.write(buffer, size);
		SumModulo(buffer, size,256,outfile2);
		cout << "Zapisano dane z bledami do innego pliku, suma modulo na koncu " << endl;
	}

	if (option == 3)
	{
		outfile.write(buffer, size);
		SumModulo(buffer, size,256, outfile);
		cout << "Zapisano bufor do pliku, suma modulo na koncu " << endl;
		infile2.read(buffer, size);
		cout << "Przeczytano nowy plik" << endl;
		RandomMistakeWithoutRepetition(buffer, size, percent1);
		outfile2.write(buffer, size);
		SumModulo(buffer, size ,256, outfile2);
		cout << "Zapisano dane z bledami do innego pliku, suma modulo na koncu " << endl;
	}
	if (option == 4)
	{
		outfile.write(buffer, size);
		CRC(buffer, size, len, outfile, outfile2, false, percent1);
		//cout << "Zapisano bufor do pliku, CRC na koncu " << endl;
		//infile2.read(buffer, size);
		//cout << "Przeczytano nowy plik" << endl;
		//RandomMistake(buffer, size, percent1);
		//outfile2.write(buffer, size);
		//crc(buffer, size, 256, outfile2);
		cout << "Zapisano dane z bledami do innego pliku, CRC na koncu " << endl;
	}
	if (option == 5)
	{
		outfile.write(buffer, size);
		CRC(buffer, size, len , outfile, outfile2, true, percent1);
		cout << "Zapisano bufor do pliku, CRC na koncu " << endl;
		//infile2.read(buffer, size);
		//cout << "Przeczytano nowy plik" << endl;
		//RandomMistakeWithoutRepetition(buffer, size, percent1);
		//outfile2.write(buffer, size);
		//crcCheck(buffer, 5, 4, infile2);
		cout << "Zapisano dane z bledami do innego pliku, CRC na koncu " << endl;
	}

	// release dynamically-allocated memory
	delete[] buffer;

	outfile.close();
	infile.close();
	outfile2.close();
	infile2.close();
	cout << endl;
}


int main() 
{
	int a, b, d;
	double c;
	cout << "Ktora operacje na pliku chcesz wykonac ?\n Bit parzystosci : 1\n Suma modulo: 2\n CRC: 3\n";
	cin >> a;
	cout << "Jakie bledy wykonac ?\n Z powtorzeniami: 1 \n Bez powtorzen: 2\n";
	cin >> b;
	cout << "Jaki procent bledow wykonac ? \n";
	cin >> c;
	
	if (a == 3) 
	{
		cout << "Podaj dlugosc generatora: \n";
		cin >> d;
	}

	if (a == 1 && b == 1) MakeFile(0, c, 0);
	if (a == 1 && b == 2) MakeFile(1, c, 0);
	if (a == 2 && b == 1) MakeFile(2, c, 0);
	if (a == 2 && b == 2) MakeFile(3, c, 0);
	if (a == 3 && b == 1) MakeFile(4, c, d);
	if (a == 3 && b == 2) MakeFile(5, c, d);

	cout << endl;
	system("pause");
	return 0;
}

