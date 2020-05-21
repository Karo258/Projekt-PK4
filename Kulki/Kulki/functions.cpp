#include <iostream>
#include <cstdlib>
#include <ctime>

#include "functions.h"

void losowanie_kulek(std::vector < std::vector<Field*>>& pola, Ball * & kulka)
{
	srand(time(NULL));
	int random_row = rand() % 8;
	int random_column = rand() % 8;
	while (pola[random_row][random_column]->is_full())
	{
		
		random_row = rand() % 8;
		random_column = rand() % 8;
	}
	kulka->change_coordinates((random_row + 1) * 70 + 35, (random_column + 1) * 70 + 35, 20);
	kulka->draw();
	pola[random_column][random_row]->set_full();
	std::cout << pola[random_row][random_column]->is_full() << " " << random_row << " " << random_column << std::endl;
}
