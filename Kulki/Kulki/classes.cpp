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

bool Field::is_mouse_over()
{
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);
	if ((state.x >= x_begin) && (state.x <= (x_begin + 70)) && (state.y >= y_begin) && (state.y <= (y_begin + 70)))
	{
		al_draw_filled_rectangle(x_begin, y_begin, x_begin + 70, y_begin + 70, al_map_rgb(130, 130, 130));
		al_draw_line(x_begin, y_begin + 70, x_begin + 70, y_begin + 70, al_map_rgb(0, 0, 0), 1);
		al_draw_line(x_begin + 70, y_begin, x_begin + 70, y_begin + 70, al_map_rgb(0, 0, 0), 1);
		return true;
	}
	else
		return false;
}

void Field::draw()
{	
	al_draw_line(x_begin, y_begin, x_begin + 70, y_begin,al_map_rgb(0,0,0),1);
	al_draw_line(x_begin, y_begin, x_begin, y_begin + 70, al_map_rgb(0, 0, 0), 1);
	al_draw_filled_rectangle(x_begin, y_begin, x_begin + 70, y_begin + 70, al_map_rgb(195, 195, 195));
}

void Field::set_full()
{
	is_ball = true;
}

bool Field::is_full()
{
	return is_ball;
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
