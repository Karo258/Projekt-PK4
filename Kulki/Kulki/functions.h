#pragma once

#include <vector>

#include "classes.h"

bool operator==(const ALLEGRO_COLOR & c, const ALLEGRO_COLOR & c2);

//funkcja jest funkcj� inline, poniewa� tylko taka funkcja mo�e by� funkcj� szablonow�
template <class T>
void delete_vector(std::vector<T>& wektor)	//funkcja realizuj�ca usuwanie z wektora
{
	for (int i = 0; i < wektor.size(); i++)
		delete wektor[i];
}

//funkcja realizuj�ca losowanie nadchodz�cych kulek
void losuj_kulki(std::vector<Ball*> & wektor);
