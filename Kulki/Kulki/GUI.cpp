#include <iostream>
#include <string.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "GUI.h"

Button::Button(int x, int y, const char* file)
{
	this->x_begin = x;
	this->y_begin = y;
	this->filename = file;
}

void Button::draw()
{
	ALLEGRO_BITMAP * B = al_load_bitmap(filename);
	al_draw_bitmap(B, x_begin, y_begin, 0);
}

CommingBalls::CommingBalls()
{
	this->x_begin = 850;
	this->y_begin = 85;
}

void CommingBalls::draw()
{
	al_draw_filled_rectangle(x_begin, y_begin, x_begin + 120, y_begin + 135, al_map_rgb(195, 195, 195));
	al_draw_filled_rectangle(x_begin + 120, y_begin, x_begin + 125, y_begin + 135, al_map_rgb(30, 110, 135));
	al_draw_filled_rectangle(x_begin + 125, y_begin, x_begin + 245, y_begin + 135, al_map_rgb(195, 195, 195));
	al_draw_filled_rectangle(x_begin + 245, y_begin, x_begin + 250, y_begin + 135, al_map_rgb(30, 110, 135));
	al_draw_filled_rectangle(x_begin + 250, y_begin, x_begin + 370, y_begin + 135, al_map_rgb(195, 195, 195));
}

TextField::TextField(int x, int y)
{
	this->x_begin = x;
	this->y_begin = y;
}

void TextField::draw()
{
	al_draw_filled_rectangle(x_begin, y_begin, x_begin + 370, y_begin + 135, al_map_rgb(195,195,195));
}