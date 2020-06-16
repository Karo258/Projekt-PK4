#pragma once

#include <allegro5/allegro.h>

class GUIObject	//wirtualna klasa bazowa dla obiektów graficznego interfejsu u¿ytkownika
{
protected:
	int x_begin; //wspó³rzêdne pocz¹tku obiektu
	int y_begin;
public:
	virtual void draw() = 0;	//wirtualna funkcja realizuj¹ca wyrysowanie obiektu graficznego
};

//I poziom dziedziczenia
class Button : public GUIObject	//klasa przycisk, zawieraj¹ca funkcjonalnoœci dla przycisków w interfejsie
{
	const char* filename; //nazwa pliku, z którego ³adowana jest bitmapa
public:
	Button(int x, int y, const char* file); //konstruktor przycisku
	void draw(); //funkcja realizuj¹ca wyrysowanie obiektu przycisk
};

class CommingBalls : public GUIObject //klasa nadchodz¹ce kulki, zawieraj¹ca funkcjonalnoœci dla pola, na którym wyœwietlane bêd¹ nadchodz¹ce kulki
{
public:
	CommingBalls(); //konstruktor obiektu nadchodz¹cych kulek
	void draw(); //wyrysowanie obiektu nadchodz¹cych kulek
};

class TextField : public GUIObject	//klasa pole tekstowe, przechowuj¹ca funkcjonalnoœci dla pól w których wyœwietlany bêdzie tekst
{
public:
	TextField(int x, int y); //konstruktor obiektu pole tekstowe
	void draw();	//wyrysowanie pola tekstowego
};