#include <iostream>

#include "exceptions.h"

void al_init_error::message()
{
	std::cout << "Could not initialize Allegro5!" << std::endl;
}

void al_mouse_init_error::message()
{
	std::cout << "Could not initialize mouse!" << std::endl;
}
