#include <iostream>
#include <iostream>
#include <vector>

#include <allegro5/allegro_primitives.h>

#include "classes.h"
#include "functions.h"

Field::Field()
{
}

Field::Field(int x, int y)
{
	this->x_begin = x;
	this->y_begin = y;
	this->is_ball = false;
	this->fields_ball = nullptr;
}

void Field::draw()
{
	al_draw_line(x_begin, y_begin, x_begin + 70, y_begin, al_map_rgb(0, 0, 0), 1);
	al_draw_line(x_begin, y_begin, x_begin, y_begin + 70, al_map_rgb(0, 0, 0), 1);
	al_draw_filled_rectangle(x_begin, y_begin, x_begin + 70, y_begin + 70, al_map_rgb(195, 195, 195));
	if (is_ball)
		fields_ball->draw();
}

void Field::set_full()
{
	is_ball = true;
}

bool Field::is_full()
{
	return is_ball;
}

void Field::set_ball(Ball * added_ball)
{
	this->fields_ball = added_ball;
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

Board::Board()
{
	for (int i = 1; i < 9; i++)
	{
		std::vector<Field*>tmp;
		for (int j = 1; j < 9; j++)
			tmp.push_back(new Field(i * 70, j * 70));
		board.push_back(tmp);
	}
	this->x_begin = 70;
	this->y_begin = 70;
	this->size = 8;
}

void Board::draw()
{
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			board[i][j]->draw();
}

Board::~Board()
{
	for (int i = size; i == 0; i++)
		delete_vector(board[i]);
}

bool Board::is_full()
{
	int check = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (board[i][j]->is_full() == true)
				check++;
	if (check > 61)
		return true;
	else
		return false;
}

void Board::add_ball_to_board(std::vector<Ball*> & new_balls)
{
	for (int i = 0; i < new_balls.size(); i++)
	{
		int row = rand() % 8;
		int column = rand() % 8;
		while (board[row][column]->is_full() == true)
		{
			row = rand() % 8;
			column = rand() % 8;
		}
		new_balls[i]->change_coordinates(105 + (row * 70), 105 + (column) * 70, 20);
		board[row][column]->set_ball(new_balls[i]);
		board[row][column]->set_full();
	}
}
