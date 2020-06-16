#include "list.h"

#include <iostream>

void lista::dodaj_na_koniec(int liczba_punktow)
{
    auto TMP = std::make_shared<element_listy>(liczba_punktow);
    if (!pHead)
        pHead = std::move(TMP);
    else
    {
        auto temp = pHead;
        while (temp->pNext)
            temp = temp->pNext;
        temp->pNext = std::move(TMP);
    }
}

void lista::usun_z_konca()
{
    if (pHead)
    {
        auto temp = pHead;
        while (temp->pNext->pNext != nullptr)
            temp = temp->pNext;
        temp->pNext.reset();
        temp->pNext = nullptr;
    }
}

void lista::usun_liste()
{
    while (pHead->pNext != nullptr)
        usun_z_konca();
    pHead.reset();
    pHead = nullptr;
}

void lista::wypisanie_listy()
{
    if (pHead)
    {
        auto temp = pHead;
        while (temp)
        {
            std::cout << temp->wynik << std::endl;
            temp = temp->pNext;
        }
    }
}

std::string lista::pierwszy_element()
{
	return std::to_string(pHead->wynik);
}

std::string lista::wypisz_element(int numer_elementu)
{
    auto tmp = pHead;
    for (int i = 0; i < numer_elementu; i++)
       tmp = tmp->pNext;
    return std::to_string(tmp->wynik);
}

void lista::dodaj_w_odpowiednim_miejscu(int wynik)
{
	auto tmp = std::make_shared<element_listy>(wynik);
	auto current = std::move(tmp);
	if (!pHead || pHead->wynik < wynik) {
		current->pNext = pHead;
		pHead = current;
		return;
	}
	else {
		auto temp = pHead;
		while (temp->pNext) 
		{
			if (temp->pNext->wynik <= wynik) {
				current->pNext = temp->pNext;
				temp->pNext = current;
				return;
			}
			temp = temp->pNext;
		}
		temp->pNext = current;
		return;
	}
}

