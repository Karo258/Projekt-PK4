#include <iostream>
#include <cstdlib>
#include <ctime>

#include "functions.h"

void new_game()
{
	std::cout << "NEW GAME" << std::endl;
	//wyzerowaæ pola planszy
	//zapisanie wyniku do listy jednokierunkowej + wyzerowanie aktualnego wyniku
	//wyzerowanie wektora zawieraj¹cego wylosowane kulki - ten wektor muszê jeszcze stworzyæ
}

void reset()
{
	std::cout << "RESET" << std::endl;
}

void end_game(bool &status)
{
	status = true;
}

void losuj_kulki(std::vector<Ball*>& wektor)
{
	for (int i = 0; i < 3; i++)
	{
		int x;
		int tmp = rand() % 4;
		if (i == 0)
			x = 913;
		else if (i == 1)
			x = 1035;
		else
			x = 1158;
		switch (tmp)
		{
		case 0:
		{
			wektor.push_back(new Ball(x, 150, al_map_rgb(255, 0, 0), 40));
			break;
		}
		case 1:
		{
			wektor.push_back(new Ball(x, 150, al_map_rgb(0, 0, 255), 40));
			break;
		}
		case 2:
		{
			wektor.push_back(new Ball(x, 150, al_map_rgb(0, 255, 0), 40));
			break;
		}
		case 3:
		{
			wektor.push_back(new Ball(x, 150, al_map_rgb(255, 255, 0), 40));
			break;
		}
		}

	}
}


