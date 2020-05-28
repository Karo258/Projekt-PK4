#pragma once

#include <allegro5/allegro.h>

class GUIObject	//wirtualna klasa bazowa dla obiekt�w graficznego interfejsu u�ytkownika
{
protected:
	int x_begin; //wsp�rz�dne pocz�tku obiektu
	int y_begin;
public:
	virtual void draw() = 0;	//wirtualna funkcja realizuj�ca wyrysowanie obiektu graficznego
};

//I poziom dziedziczenia
class Button : public GUIObject	//klasa przycisk, zawieraj�ca funkcjonalno�ci dla przycisk�w w interfejsie
{
	const char* filename;
public:
	Button(int x, int y, const char* file); //konstruktor przycisku
	void draw(); //funkcja realizuj�ca wyrysowanie obiektu przycisk
	bool is_mouse_over();
	bool is_mouse_clicked();
};

class CommingBalls : public GUIObject //klasa nadchodz�ce kulki, zawieraj�ca funkcjonalno�ci dla pola, na kt�rym wy�wietlane b�d� nadchodz�ce kulki
{
public:
	CommingBalls(); //konstruktor obiektu nadchodz�cych kulek
	void draw(); //wyrysowanie obiektu nadchodz�cych kulek
};

class TextField : public GUIObject	//klasa pole tekstowe, przechowuj�ca funkcjonalno�ci dla p�l w kt�rych wy�wietlany b�dzie tekst
{
public:
	TextField(int x, int y);
	void draw();
};

//II poziom dziedziczenia 
class ScoreDisplay : public TextField	//klasa wy�wietlacz wyniku przechowuj�ca funkcjonalno�ci do wy�wietlania wynik�w
{
//public:
//	void draw();
};