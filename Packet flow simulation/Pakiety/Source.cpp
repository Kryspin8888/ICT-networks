#include <iostream>
#include <fstream> 
#include <ctime>
#include<iomanip>

using namespace std;

bool WasValueDrawn(int iLiczba, int tab[], int ile);
void MakePackages(int MaxPackageSize, char* buffer, char* buffer1, int *HowManyPackages, short SizeOfStructPackage, int size);
void SendPackages(char* buffer, char* buffer1, int HowManyPackages, short SizeOfStructPackage, int size);

struct package
{
	uint32_t order;
	int size1;
};

int main()
{
	std::ifstream infile("bbb.txt", std::ifstream::binary);
	std::ofstream outfile("new.txt", std::ofstream::binary);

	infile.seekg(0, infile.end);
	long size1 = infile.tellg();
	infile.seekg(0);
	char* buffer1 = new char[size1];
	infile.read(buffer1, size1);

	short SizeOfStructPackage1 = sizeof(package);
	char* buffer11 = new char[size1*SizeOfStructPackage1];
	int MaxPackageSize1;
	int HowManyPackages1 = 0;

	cout << "Rozmiar twojego pliku to " << size1 << " danych typu CHAR = 1 BAJT" << endl;
	cout << "Podaj maksymalny rozmiar pakietu " << endl;
	cout << "[Wartosci mniejsze niz 10 spowoduja dluzsze dzialanie programu - zapis od konca]\n";
	cout << "[Wartosci mniejsze niz 50 spowoduja dluzsze dzialanie programu - losowanie bez powtorzen]\nPodaj rozmiar:\n";
	cin >> MaxPackageSize1;

	MakePackages(MaxPackageSize1, buffer1, buffer11, &HowManyPackages1, SizeOfStructPackage1, size1);
	SendPackages(buffer1, buffer11, HowManyPackages1, SizeOfStructPackage1, size1);

	outfile.write(buffer1, size1);
	cout << "Zapisano nowy plik" << endl;

	delete[] buffer1;
	delete[] buffer11;
	outfile.close();
	infile.close();
	cout << endl;
	system("pause");
	return 0;
}

bool WasValueDrawn(int iLiczba, int tab[], int ile)
{
	int i = 0;

	if (ile <= 0)
		return false;
	do
	{
		if (tab[i] == iLiczba)
			return true;

		i++;
	} while (i < ile);

	return false;
}

void MakePackages(int MaxPackageSize, char* buffer, char* buffer1, int *HowManyPackages, short SizeOfStructPackage,int size)
{
	int PackageSize = 0;
	long size_pom = size;
	int PackageSizePom = 0;
	int BufPom = 0;

	srand(time(NULL));

	cout << "Tworzenie pakietow o losowej wielkosci\n";

	for (int i = 0; i <= size_pom; i++)
	{
		do
		{
			PackageSize = 1 + rand() % MaxPackageSize;	// losowanie wielkosci pakietu z przedzialu
		} while (PackageSize + PackageSizePom > size);

		char* MyPackage = new char[SizeOfStructPackage + PackageSize];
		package* p = (package*)MyPackage;								// wskaznik na poczatek pakietu
		(*p).order = i;
		(*p).size1 = PackageSize;

		for (int j = SizeOfStructPackage; j < SizeOfStructPackage + PackageSize; j++)
		{
			MyPackage[j] = buffer[j - SizeOfStructPackage + PackageSizePom];
		}
		for (int k = 0; k < PackageSize + SizeOfStructPackage; k++)
		{
			buffer1[k + BufPom] = MyPackage[k];			//zapis pakietow do innego bufora
		}
		BufPom += (PackageSize + SizeOfStructPackage);

		PackageSizePom += PackageSize;

		if (size_pom - PackageSize <= i && PackageSizePom<size)
			size_pom = size - PackageSizePom + i;
		else
			size_pom -= PackageSize;

		*HowManyPackages+=1;
	}

	cout << "Stworzono: " << *HowManyPackages << " pakietow" << endl;
}

void SendPackages(char* buffer, char* buffer1, int HowManyPackages, short SizeOfStructPackage,int size)
{
	for (int i = 0; i < size; i++)
		buffer[i] = '0';

	int WhichPackage = rand() % (HowManyPackages);
	int i = 0;
	long long ActualPosition = 0;
	int* WasDrawn = new int[HowManyPackages];
	bool How;

	for (int t = 0; t < HowManyPackages; t++)
		WasDrawn[t] = -1;
	WasDrawn[0] = WhichPackage;

	cout << "Podaj w jaki sposob chcesz przesylac pakiety?\n";
	cout << "Wpisz 0 - zapis od ostaniego do pierwszego\n";
	cout << "Wpisz 1 - losowanie bez powtorzen kolejnosci pakietow podaj\n";
	cin >> How;
	cout << "Rozpoczeto zapis\n";

	for (int j = 0; j<HowManyPackages; j++)
	{
		if (How) {
			if (j > 0)
			{
				WhichPackage = rand() % (HowManyPackages);		//losowanie kolejnosci pakietow
			}

			while (WasValueDrawn(WhichPackage, WasDrawn, j))
			{
				WhichPackage = rand() % (HowManyPackages);
			}
			WasDrawn[j] = WhichPackage;
		}
		else if (!How) WhichPackage = HowManyPackages - 1 - j;

		package *n = reinterpret_cast<package*>(&buffer1[ActualPosition]);

		for (i = 0; i <= WhichPackage - 1; i++)
		{
			ActualPosition += (*n).size1 + SizeOfStructPackage;		//wyznaczenie poczatku danych pakietu
			n = reinterpret_cast<package*>(&buffer1[ActualPosition]);
		}

		for (long long k = ActualPosition + 8; k < ActualPosition + SizeOfStructPackage + (*n).size1; k++)
			buffer[k - (WhichPackage + 1)*SizeOfStructPackage] = buffer1[k];		//zapis samych danych do bufora
		ActualPosition = 0;
	}

	delete[] WasDrawn;
}
