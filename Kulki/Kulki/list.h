#pragma once

#include <memory>
#include <string>

struct element_listy {
    std::string wynik;
    std::shared_ptr<element_listy> pNext;
    element_listy(std::string liczba_punktow) : wynik(liczba_punktow), pNext(nullptr) {};
};

class lista {
    std::shared_ptr<element_listy> pHead;
public:
    void dodaj_na_koniec(std::string liczba_punktow);
    void usun_z_konca();
    void usun_liste();
    void wypisanie_listy();
	std::string pierwszy_element();
    std::string wypisz_element(int numer_elementu);
};

