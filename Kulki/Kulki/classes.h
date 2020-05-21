#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

class GraphicalObject	//wirtualna klasa bazowa
{
protected:
	int x_begin; //wspó³rzêdne pocz¹tku obiektu
	int y_begin;
public:
	virtual void draw() = 0;
};

//I poziom dziedziczenia
class Field : public GraphicalObject //klasa pole gry, zawieraj¹ca funkcjonalnoœci dla pojedynczego pola planszy
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
	void change_coordinates(int x, int y, int r); //metoda realizuj¹ca zmianê wspó³rzêdnych po³o¿enia kulki (w celu jej wyœwietlenia na odpowiednim polu planszy)
};

//II poziom dziedziczenua
class Board : public Field	//klasa plansza, zawieraj¹ca funkcjonalnoœci dla planszy jako ca³oœci
{

};