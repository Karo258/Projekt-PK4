#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

class GraphicalObject		 //wirtualna klasa bazowa
{
protected:
	int x_begin;			 //wspó³rzêdne pocz¹tku obiektu
	int y_begin;
public:
	virtual void draw() = 0; //wirtualna funkcja realizuj¹ca wyrysowanie obiektu graficznego
};

//I poziom dziedziczenia
class Field : public GraphicalObject //klasa pole gry, zawieraj¹ca funkcjonalnoœci dla pojedynczego pola planszy
{
protected:
	bool is_ball;					//zmienna przechowuj¹ca informacjê o tym czy na danym polu znajduje siê kulka
public:
	Field(int x, int y);			//konstruktor obiektu pola
	bool is_mouse_over();			//funkjca realizuj¹ca zmianê koloru pola, po najechaniu na nie mysz¹
	void draw();					//funkcja realizuj¹ca wyrysowanie obiektu pola
	void set_full();				//funkcja ustawiaj¹ca pole is_ball na wartoœæ true
	bool is_full();					//funkcja zwracaj¹ca informacjê o tym, czy pole is_ball ma wartoœæ true
};

class Ball : public GraphicalObject					//klasa kulka, zawieraj¹ca funkcjonalnoœci dla kulek
{
protected:
	ALLEGRO_COLOR color;							//kolor kulki
	int radius;										//promieñ kulki
public:
	Ball(int x, int y, ALLEGRO_COLOR c, int r);		//konstruktor obiektu kulki
	void draw();									//funkcja realizuj¹ca wyrysowanie obiektu kulki
	void change_coordinates(int x, int y, int r);	//metoda realizuj¹ca zmianê wspó³rzêdnych po³o¿enia kulki (w celu jej wyœwietlenia na odpowiednim polu planszy)
};

//II poziom dziedziczenua
class Board : public Field	//klasa plansza, zawieraj¹ca funkcjonalnoœci dla planszy jako ca³oœci
{

};