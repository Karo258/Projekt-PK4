#pragma once

#include <memory>
#include <string>

//struktura elementu listy jednokierunkowej
struct element_listy {
    std::string wynik;																		//przechowywana w li�cie warto�� - wynik
    std::shared_ptr<element_listy> pNext;													//wska�nik na kolejny element listy
    element_listy(std::string liczba_punktow) : wynik(liczba_punktow), pNext(nullptr) {};	//konstruktor elementu listy
};

//klasa listy jednokierunkowej
class lista {
    std::shared_ptr<element_listy> pHead;				//wska�nik na g�ow� listy (pierwszy element)
public:
    void dodaj_na_koniec(std::string liczba_punktow);	//metoda realizuj�ca dodawanie element�w na koniec listy jednokierunkowej
    void usun_z_konca();								//metoda realizuj�ca usuwanie ostatniego elementu listy jednokierunkowej
    void usun_liste();									//metoda realizuj�ca usuwanie listy jednokierunkowej
    void wypisanie_listy();								//metoda realizuj�ca wypisanie listy jednokierunkowej
	std::string pierwszy_element();						//metoda zwracaj�ca pierwszy element listy jednokierunkowej
    std::string wypisz_element(int numer_elementu);		//metoda zwracaj�ca element o podanym numerze
};

