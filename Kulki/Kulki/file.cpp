#include "file.h"
#include "list.h"

#include <iostream>
#include <fstream>

void read_from_file(const std::string filename, lista* moja_lista)
{
	//otwarcie pliku
	std::ifstream plik_wejsciowy(filename);
	
	std::string s;
	if (plik_wejsciowy.good() == true)
	{
		while (!plik_wejsciowy.eof())
		{
			int punkty;
			plik_wejsciowy >> punkty;
			moja_lista->dodaj_na_koniec(punkty);
		}
	}
	//zamkniêcie pliku
	plik_wejsciowy.close();
}

void write_to_file(std::string filename, lista* & moja_lista)
{
	//otwarcie pliku
	std::ofstream plik_wyjsciowy(filename);

	for (int i = 0; i < 8; i++) //8 - poniewa¿ chcê, by zapisywane do pliku by³o tylko 8 najlepszych wyników
	{
		plik_wyjsciowy << moja_lista->wypisz_element(i) << "\n";
	}

	//usuniêcie listy jednokierunkowej
	moja_lista->usun_liste();

	//zamkniêcie pliku
	plik_wyjsciowy.close();
}
