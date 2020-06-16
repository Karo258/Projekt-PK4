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

Ball * Field::get_ball()
{
	return this->fields_ball;
}

Field * Field::is_mouse_clicked()
{
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);
	if ((state.x >= x_begin) && (state.x <= x_begin + 70) && (state.y >= y_begin) && (state.y <= y_begin + 70))
	{
		if (al_mouse_button_down(&state, 1))
		{
			return this;
		}
	}
}

int Field::get_x()
{
	return this->x_begin;
}

int Field::get_y()
{
	return this->y_begin;
}

void Field::set_empty()
{
	this->is_ball = false;
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

ALLEGRO_COLOR Ball::get_color()
{
	return this->color;
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

void Board::swap(int& x1, int& y1, int& x2, int& y2)
{
	bool is_there_ball1 = false;
	bool is_there_ball2 = true;
	int row1, column1, row2, column2;
	Ball* tmp;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (x1 == board[i][j]->get_x() && y1 == board[i][j]->get_y())
			{
				is_there_ball1 = board[i][j]->is_full();
				row1 = i;
				column1 = j;
			}
			if (x2 == board[i][j]->get_x() && y2 == board[i][j]->get_y())
			{
				is_there_ball2 = board[i][j]->is_full();
				row2 = i;
				column2 = j;
			}
		}
	}
	if ((is_there_ball1) && (!is_there_ball2))
	{
		tmp = board[row1][column1]->get_ball();
		tmp->change_coordinates(105 + (row2 * 70), 105 + (column2 * 70), 20);
		board[row2][column2]->set_ball(tmp);
		board[row2][column2]->set_full();
		board[row1][column1]->set_ball(nullptr);
		board[row1][column1]->set_empty();
	}
}

void Board::deleting(int & wynik, int& counter)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size-1; j++)
		{
			if (board[i][j]->is_full() && board[i][j+1]->is_full())
			{
				if (board[i][j]->get_ball()->get_color() == board[i][j + 1]->get_ball()->get_color())
				{
					counter++;
				}
				else
				{
					counter = 1;
				}

				if (counter > 4)
				{
					int tmp = j+1;
					for (int k = counter+1; k >= 0; k--)
					{
						if (tmp >= 0)
						{
							board[i][tmp]->set_ball(nullptr);
							board[i][tmp]->set_empty();
							wynik++;
							tmp--;
						}
					}	
				}
				std::cout << counter << std::endl;
			}	
		}
		counter = 1;
	}
}
