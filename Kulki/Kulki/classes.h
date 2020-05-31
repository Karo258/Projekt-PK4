#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

class GraphicalObject		 //wirtualna klasa bazowa
{
protected:
	int x_begin;			 //wsp�rz�dne pocz�tku obiektu
	int y_begin;
public:
	virtual void draw() = 0; //wirtualna funkcja realizuj�ca wyrysowanie obiektu graficznego
};

//I poziom dziedziczenia
class Field : public GraphicalObject //klasa pole gry, zawieraj�ca funkcjonalno�ci dla pojedynczego pola planszy
{
protected:
	bool is_ball;					//zmienna przechowuj�ca informacj� o tym czy na danym polu znajduje si� kulka
public:
	Field(int x, int y);			//konstruktor obiektu pola
	bool is_mouse_over();			//funkjca realizuj�ca zmian� koloru pola, po najechaniu na nie mysz�
	void draw();					//funkcja realizuj�ca wyrysowanie obiektu pola
	void set_full();				//funkcja ustawiaj�ca pole is_ball na warto�� true
	bool is_full();					//funkcja zwracaj�ca informacj� o tym, czy pole is_ball ma warto�� true
};

class Ball : public GraphicalObject					//klasa kulka, zawieraj�ca funkcjonalno�ci dla kulek
{
protected:
	ALLEGRO_COLOR color;							//kolor kulki
	int radius;										//promie� kulki
public:
	Ball(int x, int y, ALLEGRO_COLOR c, int r);		//konstruktor obiektu kulki
	void draw();									//funkcja realizuj�ca wyrysowanie obiektu kulki
	void change_coordinates(int x, int y, int r);	//metoda realizuj�ca zmian� wsp�rz�dnych po�o�enia kulki (w celu jej wy�wietlenia na odpowiednim polu planszy)
};

//II poziom dziedziczenua
class Board : public Field	//klasa plansza, zawieraj�ca funkcjonalno�ci dla planszy jako ca�o�ci
{

};