#pragma once

#include <vector>

#include "classes.h"

//funkcja jest funkcj¹ inline, poniewa¿ tylko taka funkcja mo¿e byæ funkcj¹ szablonow¹
template <class T>
void delete_vector(std::vector<T>& wektor)
{
	for (int i = 0; i < wektor.size(); i++)
		delete wektor[i];
}

void losowanie_kulek(std::vector < std::vector<Field*>>& pola, Ball* & kulka);