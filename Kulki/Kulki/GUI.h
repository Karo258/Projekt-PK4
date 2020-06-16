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
	const char* filename; //nazwa pliku, z którego ładowana jest bitmapa
public:
	Button(int x, int y, const char* file); //konstruktor przycisku
	void draw(); //funkcja realizująca wyrysowanie obiektu przycisk
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
	TextField(int x, int y); //konstruktor obiektu pole tekstowe
	void draw();	//wyrysowanie pola tekstowego
};