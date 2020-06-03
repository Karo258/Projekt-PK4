#include <iostream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "exceptions.h"
#include "GUI.h"
#include "list.h"
#include "classes.h"
#include "functions.h"
#include "file.h"

int main()
{
	try //obs³uga b³êdu zwi¹zanego z brakiem mo¿liwoœci inicjalizacji biblioteki allegro
	{
		if (!al_init())	//inicjalizacja biblioteki allegro
		{
			al_init_error init_error;
			throw init_error;
		}
	}
	catch (al_init_error error)
	{
		error.message();
		return -1;
	}

	//inicjalizacja elementów biblioteki graficznej Allegro 5
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY * main_display = al_create_display(1280, 720);	//utworzenie okna gry
	al_set_window_title(main_display, "KULKI"); //zatytu³owanie okna gry
	al_clear_to_color(al_map_rgb(30, 110, 125)); //ustawienie koloru t³a okna gry

	
	try //obs³uga b³êdu zwi¹zanego z brakiem mo¿liwoœci instalacji myszy
	{
		if (!al_install_mouse())	//instalacja myszy
		{
			al_mouse_init_error init_error;
			throw init_error;
		}
	}
	catch (al_mouse_init_error error)
	{
		error.message();
		return -1;
	}
	//utworzenie kursora myszy
	ALLEGRO_MOUSE_STATE mouse;
	al_get_mouse_state(&mouse);
	al_set_system_mouse_cursor(main_display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_show_mouse_cursor(main_display);

	//utworzenie kolejki zdarzeñ
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(main_display));	//ustawienie okna gry jako Ÿród³a zdarzeñ
	al_register_event_source(event_queue, al_get_mouse_event_source());	//ustawienie myszy jako Ÿród³a zdarzeñ

	//utworzenie czcionek
	ALLEGRO_FONT* ttf_font = al_load_ttf_font("arial.ttf", 24, 0);	//o wielkoœci 24
	ALLEGRO_FONT* big_ttf_font = al_load_ttf_font("arial.ttf", 128, 0); // o wielkoœci 128

	//utworzenie wektora przycisków
	std::vector<Button*> vector_of_buttons;
	vector_of_buttons.push_back(new Button(650, 85, "NG_normal.png")); 
	vector_of_buttons.push_back(new Button(650, 287, "RESET_normal.png"));
	vector_of_buttons.push_back(new Button(650, 485, "EG_normal.png"));

	//utworzenia pola, na którym bêd¹ siê pojawia³y nadchodz¹ce kulki
	al_draw_text(ttf_font, al_map_rgb(195, 195, 195), 850, 50, 0, "KOLEJNE KULKI");
	CommingBalls nadchodzace_kulki = CommingBalls();
	nadchodzace_kulki.draw();

	//utworzenie pol tekstowych, na ktorych pojawi¹ siê wyniki
	al_draw_text(ttf_font, al_map_rgb(195, 195, 195), 850, 252, 0, "AKTUALNY WYNIK");
	TextField aktualny_wynik = TextField(850, 287);
	aktualny_wynik.draw();
	al_draw_text(ttf_font, al_map_rgb(195, 195, 195), 850, 450, 0, "NAJLEPSZY WYNIK");
	TextField najlepszy_wynik = TextField(850, 485);
	najlepszy_wynik.draw();

	//utworzenie pól gry
	Board pola_planszy;
	pola_planszy = Board();

	//wynik na pocz¹tku dzia³ania programu
	const char* twoj_wynik = "0 0 0";
	al_draw_text(big_ttf_font, al_map_rgb(0, 0, 0), 890, 280, 0, twoj_wynik);
	
	//utworzenie jednokierunkowej listy wyników
	lista* score_list = new lista();

	//wczytanie wyników z pliku do listy jednokierukowej
	read_from_file("tabela_wynikow.txt", score_list);
	char* najwyzszy_wynik = new char[score_list->pierwszy_element().length()+1];
	std::strcpy(najwyzszy_wynik, score_list->pierwszy_element().c_str());
	al_draw_text(big_ttf_font, al_map_rgb(0, 0, 0), 890, 480, 0, najwyzszy_wynik);
	
	//stworzenie wektora nadchodz¹cych kulek
	std::vector<Ball*> balls;
	losuj_kulki(balls);
	for (int i = 0; i < balls.size(); i++)
		balls[i]->draw();

	std::vector<Ball*> new_balls;

	bool end = false; //zmienna lokalna przechowuj¹ca warunek g³ównej pêtli programu
	srand(time(NULL));
	while (!end) //g³ówna pêtla programu
	{
		//wyrysowanie przycisków
		for (int i = 0; i < vector_of_buttons.size(); i++)
			vector_of_buttons[i]->draw();
		
		//zmiana przycisku po najechaniu na niego mysz¹
		for (int i = 0; i < vector_of_buttons.size(); i ++)
		{
			bool covered = vector_of_buttons[i]->is_mouse_over();
			if (covered == true)
				i = vector_of_buttons.size();
		}

		//wywo³anie akcji zwi¹zanych z przyciskami
		for (int i = 0; i < vector_of_buttons.size(); i++)
		{
			bool  clicked = vector_of_buttons[i]->is_mouse_clicked(end);
			if (clicked)
				i = vector_of_buttons.size();
		}

		//wyrysowanie planszy
		pola_planszy.draw();

		//zmiana pola planszy po najechaniu na nie mysz¹
		pola_planszy.is_mouse_over();

		//przepisanie poprzednio wylosowanych kulek do nowego wektora
		for (int i = 0; i < balls.size(); i++)
			new_balls.push_back(balls[i]);
		
		//usuniêcie elementów wektora przechowuj¹cego nadchodzace kulki
		for (int i = balls.size(); i > 0; i--)
			balls.pop_back();

		//losowanie kulek do kolejnej rundy
		losuj_kulki(balls);
		
		//wyrysowanie nadchodz¹cych kulek
		for (int i = 0; i < balls.size(); i++)
			balls[i]->draw();

		//wyrysowanie kulek w losowych miejscach na planszy
		pola_planszy.draw_balls(new_balls);

		//pêtla do przestawiania kulek
		bool moved = false;
		while (!moved)
		{
			moved = true;
		}

		ALLEGRO_EVENT event;	//utworzenie zdarzenia
		al_wait_for_event(event_queue, &event);	//oczekiwanie na zdarzenie

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	//zamykanie okna gry za pomoc¹ przycisku "X" w prawym górnym rogu okna
			end = true;

		al_flip_display();

		//usuniecie elementow wektora przechowuj¹cego aktualne kulki
		for (int i = new_balls.size(); i > 0; i--)
			new_balls.pop_back();

		//zakoñczenie gry, gdy na planszy znajêtych bêdzie wiêcej ni¿ 61 pól - brak mo¿liwoœci wstawienia kolejnych kulek
		if (pola_planszy.is_full())
			end = true;

		//zapisanie tabeli wyników do pliku tekstowego po zakoñczeniu gry przez u¿ytkownika
		if (end)
			write_to_file("tabela_wynikow.txt", score_list);
	}

	//usuniêcie wektora przycisków
	delete_vector(vector_of_buttons);

	//usuniêcie wektora wektorów pól planszy
	pola_planszy.~Board();
	
	al_destroy_font(ttf_font); //usuniêcie czcionki o wielkoœci 24
	al_destroy_font(big_ttf_font); //usuniêcie czcionki o wielkoœci 128
	al_destroy_event_queue(event_queue); //usuniêcie kolejki zdarzeñ
	al_destroy_display(main_display); //usuniêcie okna gry
	return 0;
}