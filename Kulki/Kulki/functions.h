#pragma once

#include <vector>

#include "classes.h"

//funkcja jest funkcj� inline, poniewa� tylko taka funkcja mo�e by� funkcj� szablonow�
template <class T>
void delete_vector(std::vector<T>& wektor)	//funkcja realizuj�ca usuwanie z wektora
{
	for (int i = 0; i < wektor.size(); i++)
		delete wektor[i];
}

//funkjca realizuj�ca akcje zwi�zane z rozpocz�ciem nowej gry
void new_game();

//funkcja realizuj�ca akcje zwi�zane z restartem gry
void reset(); 

//funkcja realizuj�ca akcje zwi�zane z zako�czeniem gry
void end_game();