#pragma once

#include <allegro5/allegro.h>

class GUIObject	//wirtualna klasa bazowa dla obiektów graficznego interfejsu użytkownika
{
protected:
	int x_begin; //współrzędne początku obiektu
	int y_begin;
public:
	virtual void draw() = 0;	//wirtualna funkcja realizująca wyrysowanie obiektu graficznego
};

//I poziom dziedziczenia
class Button : public GUIObject	//klasa przycisk, zawierająca funkcjonalności dla przycisków w interfejsie
{
	const char* filename;
public:
	Button(int x, int y, const char* file); //konstruktor przycisku
	void draw(); //funkcja realizująca wyrysowanie obiektu przycisk
	//bool is_mouse_over(ALLEGRO_MOUSE_STATE mouse, );
};

class CommingBalls : public GUIObject //klasa nadchodzące kulki, zawierająca funkcjonalności dla pola, na którym wyświetlane będą nadchodzące kulki
{
public:
	CommingBalls(); //konstruktor obiektu nadchodzących kulek
	void draw(); //wyrysowanie obiektu nadchodzących kulek
};

class TextField : public GUIObject	//klasa pole tekstowe, przechowująca funkcjonalności dla pól w których wyświetlany będzie tekst
{
public:
	TextField(int x, int y);
	void draw();
};

//II poziom dziedziczenia 
class ScoreDisplay : public TextField	//klasa wyświetlacz wyniku przechowująca funkcjonalności do wyświetlania wyników
{
//public:
//	void draw();
};