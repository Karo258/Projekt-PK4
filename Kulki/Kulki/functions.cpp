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
