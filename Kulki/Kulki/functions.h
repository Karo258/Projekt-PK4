#pragma once

#include <vector>

#include "classes.h"

//funkcja jest funkcj¹ inline, poniewa¿ tylko taka funkcja mo¿e byæ funkcj¹ szablonow¹
template <class T>
void delete_vector(std::vector<T>& wektor)	//funkcja realizuj¹ca usuwanie z wektora
{
	for (int i = 0; i < wektor.size(); i++)
		delete wektor[i];
}

//funkjca realizuj¹ca akcje zwi¹zane z rozpoczêciem nowej gry
void new_game();

//funkcja realizuj¹ca akcje zwi¹zane z restartem gry
void reset(); 

//funkcja realizuj¹ca akcje zwi¹zane z zakoñczeniem gry
void end_game();