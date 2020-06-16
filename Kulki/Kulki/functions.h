#pragma once

#include <vector>

#include "classes.h"

bool operator==(const ALLEGRO_COLOR & c, const ALLEGRO_COLOR & c2);

//funkcja jest funkcj¹ inline, poniewa¿ tylko taka funkcja mo¿e byæ funkcj¹ szablonow¹
template <class T>
void delete_vector(std::vector<T>& wektor)	//funkcja realizuj¹ca usuwanie z wektora
{
	for (int i = 0; i < wektor.size(); i++)
		delete wektor[i];
}

//funkcja realizuj¹ca losowanie nadchodz¹cych kulek
void losuj_kulki(std::vector<Ball*> & wektor);
