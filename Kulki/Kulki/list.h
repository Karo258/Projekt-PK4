#pragma once

#include <memory>
#include <string>

//struktura elementu listy jednokierunkowej
struct element_listy {
    std::string wynik;																		//przechowywana w liœcie wartoœæ - wynik
    std::shared_ptr<element_listy> pNext;													//wskaŸnik na kolejny element listy
    element_listy(std::string liczba_punktow) : wynik(liczba_punktow), pNext(nullptr) {};	//konstruktor elementu listy
};

//klasa listy jednokierunkowej
class lista {
    std::shared_ptr<element_listy> pHead;				//wskaŸnik na g³owê listy (pierwszy element)
public:
    void dodaj_na_koniec(std::string liczba_punktow);	//metoda realizuj¹ca dodawanie elementów na koniec listy jednokierunkowej
    void usun_z_konca();								//metoda realizuj¹ca usuwanie ostatniego elementu listy jednokierunkowej
    void usun_liste();									//metoda realizuj¹ca usuwanie listy jednokierunkowej
    void wypisanie_listy();								//metoda realizuj¹ca wypisanie listy jednokierunkowej
	std::string pierwszy_element();						//metoda zwracaj¹ca pierwszy element listy jednokierunkowej
    std::string wypisz_element(int numer_elementu);		//metoda zwracaj¹ca element o podanym numerze
};

