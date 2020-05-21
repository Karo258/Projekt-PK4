#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

class GraphicalObject	//wirtualna klasa bazowa
{
protected:
	int x_begin; //wsp�rz�dne pocz�tku obiektu
	int y_begin;
public:
	virtual void draw() = 0;
};

//I poziom dziedziczenia
class Field : public GraphicalObject //klasa pole gry, zawieraj�ca funkcjonalno�ci dla pojedynczego pola planszy
{
protected:
	bool is_ball;
public:
	Field(int x, int y);
	void draw();
	bool is_full();
	void set_full();
};

class Ball : public GraphicalObject	
{
protected:
	ALLEGRO_COLOR color;
	int radius;
public:
	Ball(int x, int y, ALLEGRO_COLOR c, int r);
	void draw();
	void change_coordinates(int x, int y, int r); //metoda realizuj�ca zmian� wsp�rz�dnych po�o�enia kulki (w celu jej wy�wietlenia na odpowiednim polu planszy)
};

//II poziom dziedziczenua
class Board : public Field	//klasa plansza, zawieraj�ca funkcjonalno�ci dla planszy jako ca�o�ci
{

};