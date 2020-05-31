#include <iostream>
#include <iostream>

#include <allegro5/allegro_primitives.h>

#include "classes.h"

Field::Field(int x, int y)
{
	this->x_begin = x;
	this->y_begin = y;
	this->is_ball = false;
}

void Field::draw()
{	
	al_draw_line(x_begin, y_begin, x_begin + 70, y_begin,al_map_rgb(0,0,0),1);
	al_draw_line(x_begin, y_begin, x_begin, y_begin + 70, al_map_rgb(0, 0, 0), 1);
	al_draw_filled_rectangle(x_begin, y_begin, x_begin + 70, y_begin + 70, al_map_rgb(195, 195, 195));

}

Ball::Ball(int x, int y, ALLEGRO_COLOR c, int r)
{
	this->x_begin = x;
	this->y_begin = y;
	this->color = c;
	this->radius = r;
}

void Ball::draw()
{
	al_draw_filled_circle(x_begin, y_begin, radius, color);
}

void Ball::change_coordinates(int x, int y, int r)
{
	this->x_begin = x;
	this->y_begin = y;
	this->radius = r;
}
