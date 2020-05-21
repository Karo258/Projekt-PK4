#include "file.h"
#include "list.h"

#include <iostream>
#include <fstream>

void read_from_file(const std::string filename, lista* moja_lista)
{
	//otwarcie pliku
	std::ifstream plik_wejsciowy(filename);
	
	std::string s;
	while (not plik_wejsciowy.eof())
	{
		std::getline(plik_wejsciowy, s);
		moja_lista->dodaj_na_koniec(s);
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
