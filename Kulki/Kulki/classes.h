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

class Field : public GraphicalObject //klasa pole gry, zawieraj�ca funkcjonalno�ci dla pojedynczego pola planszy
{
protected:
	bool is_ball;					//zmienna przechowuj�ca informacj� o tym czy na danym polu znajduje si� kulka
	Ball* fields_ball;				//kulka znajduj�ca si� na polu
public:
	Field();
	Field(int x, int y);			//konstruktor obiektu pola
	void draw();					//funkcja realizuj�ca wyrysowanie obiektu pola
	void set_full();				//funkcja ustawiaj�ca pole is_ball na warto�� true
	bool is_full();					//funkcja zwracaj�ca informacj� o tym, czy pole is_ball ma warto�� true
	void set_ball(Ball* added_ball);//funkcja realizuj�ca dodawanie kulki do pola
	Ball* get_ball();				//funkcja zwracaj�ca kulk� pola
	Field* is_mouse_clicked();		//funkcja zwracaj�ca pole, kt�re zosta�o klikni�te
	int get_x();					//zwracanie x
	int get_y();					//zwracanie y
	void set_empty();				//
};

//II poziom dziedziczenia
class Board : public Field	//klasa plansza, zawieraj�ca funkcjonalno�ci dla planszy jako ca�o�ci
{
protected:
	std::vector<std::vector<Field*>> board;					//plansza
	int size;												//rozmiar - jeden, poniewa� plansza jest zawsze kwadratem
public:
	Board();												//konstruktor planszy
	void draw();											//wyrysowanie planszy
	~Board();												//destruktor planszy - usuwa wektor wektor�w wska�nik�w na pola planszy
	bool is_full();											//funkcja realizuj�ca sprawdzenie czy s� wolne miejsca do wstawienia kolejnych kulek
	void add_ball_to_board(std::vector<Ball*> & new_balls);	//funkcja realizuj�ca dodawanie nowych kulek na plansz�
	void swap(int& x1, int& y1, int& x2, int& y2);				//
};