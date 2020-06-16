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
	try //obs�uga b��du zwi�zanego z brakiem mo�liwo�ci inicjalizacji biblioteki allegro
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

	//inicjalizacja element�w biblioteki graficznej Allegro 5
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY * main_display = al_create_display(1280, 720);	//utworzenie okna gry
	al_set_window_title(main_display, "KULKI");						//zatytu�owanie okna gry
	al_clear_to_color(al_map_rgb(30, 110, 125));					//ustawienie koloru t�a okna gry


	try //obs�uga b��du zwi�zanego z brakiem mo�liwo�ci instalacji myszy
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
	al_set_system_mouse_cursor(main_display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_show_mouse_cursor(main_display);

	//utworzenie kolejki zdarze�
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(main_display));	//ustawienie okna gry jako �r�d�a zdarze�
	al_register_event_source(event_queue, al_get_mouse_event_source());					//ustawienie myszy jako �r�d�a zdarze�
	ALLEGRO_EVENT event;

	//utworzenie czcionek
	ALLEGRO_FONT* ttf_font = al_load_ttf_font("arial.ttf", 24, 0);			//o wielko�ci 24
	ALLEGRO_FONT* middle_ttf_font = al_load_ttf_font("arial.ttf", 64, 0);	//o wielko�ci 64
	ALLEGRO_FONT* big_ttf_font = al_load_ttf_font("arial.ttf", 128, 0);		// o wielko�ci 128

	//utworzenie wektora przycisk�w
	std::vector<Button*> vector_of_buttons;
	vector_of_buttons.push_back(new Button(650, 85, "NG_normal.png"));
	vector_of_buttons.push_back(new Button(650, 287, "RESET_normal.png"));
	vector_of_buttons.push_back(new Button(650, 485, "EG_normal.png"));

	//utworzenia pola, na kt�rym b�d� si� pojawia�y nadchodz�ce kulki
	al_draw_text(ttf_font, al_map_rgb(195, 195, 195), 850, 50, 0, "KOLEJNE KULKI");
	CommingBalls nadchodzace_kulki = CommingBalls();
	nadchodzace_kulki.draw();

	//utworzenie pol tekstowych, na ktorych pojawi� si� wyniki
	al_draw_text(ttf_font, al_map_rgb(195, 195, 195), 850, 252, 0, "AKTUALNY WYNIK");
	TextField aktualny_wynik = TextField(850, 287);
	aktualny_wynik.draw();
	al_draw_text(ttf_font, al_map_rgb(195, 195, 195), 850, 450, 0, "NAJLEPSZY WYNIK");
	TextField najlepszy_wynik = TextField(850, 485);
	najlepszy_wynik.draw();

	//utworzenie p�l gry
	Board pola_planszy;
	pola_planszy = Board();

	//wynik na pocz�tku dzia�ania programu
	const char* twoj_wynik = "0 0 0";
	al_draw_text(big_ttf_font, al_map_rgb(0, 0, 0), 890, 280, 0, twoj_wynik);

	//utworzenie jednokierunkowej listy wynik�w
	lista* score_list = new lista();

	//wczytanie wynik�w z pliku do listy jednokierukowej
	read_from_file("tabela_wynikow.txt", score_list);
	char* najwyzszy_wynik = new char[score_list->pierwszy_element().length() + 1];
	std::strcpy(najwyzszy_wynik, score_list->pierwszy_element().c_str());
	al_draw_text(big_ttf_font, al_map_rgb(0, 0, 0), 890, 480, 0, najwyzszy_wynik);

	//stworzenie wektora nadchodz�cych kulek
	std::vector<Ball*> balls;
	losuj_kulki(balls);			//wywo�anie funkcji losuj�cej 3 kulki
	for (int i = 0; i < 3; i++)
		balls[i]->draw();		//wyrysowanie nadchodz�cych kulek

	//stworzenie wektora kulek z poprzedniej rundy
	std::vector<Ball*> new_balls;

	//wyrysowanie przycisk�w
	for (int i = 0; i < vector_of_buttons.size(); i++)
		vector_of_buttons[i]->draw();

	bool end = false; //zmienna lokalna przechowuj�ca warunek g��wnej p�tli programu
	srand(time(NULL));
	while (!end) //g��wna p�tla programu
	{
		al_wait_for_event(event_queue, &event);
		pola_planszy.draw();			//wyrysowanie planszy
		al_get_mouse_state(&mouse);
		if (al_mouse_button_down(&mouse, 1))
		{
			new_balls = balls;				//przepisanie kulek do wektora kulek do wyrysowania na planszy
			balls.clear();					//usuni�cie nadchodz�cych kulek
			pola_planszy.add_ball_to_board(new_balls);	//dodanie kulek z wektora kulek do wyrysowania na planszy do planszy
			losuj_kulki(balls);				//wylosowanie nowych nadchodz�cych kulek
			for (int i = 0; i < 3; i++)
				balls[i]->draw();			//wyrysowanie nadchodz�cych kulek
			new_balls.clear();				//usuni�cie wektora kulek do wyrysowania na planszy
		}
		if (pola_planszy.is_full())
			end = true;
		al_flip_display();
	}

	//p�tla do wykonywania wszystkich opcji po zako�czeniu gry oraz wypisywania wynik�w
	bool definitive_end = false;
	while (!definitive_end)
	{
		al_clear_to_color(al_map_rgb(30, 110, 125));	//ustawienie koloru t�a 
		al_draw_filled_rounded_rectangle(290, 10, 990, 710, 20, 20, al_map_rgb(195, 195, 195));	//utworzenie t�a dla tablicy wynik�w
		al_draw_text(middle_ttf_font, al_map_rgb(0, 0, 0), 295, 45, 0, "WYNIKI:");	
		int x_pocz = 295;
		int y_pocz = 115;

		//wypisywanie tablicy wynik�w
		for (int i = 0; i < 8; i++)
		{
			char* wynik = new char[score_list->wypisz_element(i).length() + 1];
			std::strcpy(wynik, score_list->wypisz_element(i).c_str());
			al_draw_text(middle_ttf_font, al_map_rgb(0, 0, 0), x_pocz, y_pocz, 0, wynik);
			y_pocz += 70;
		}

		//utworzenie zdarzenia
		al_wait_for_event(event_queue, &event);	//oczekiwanie na zdarzenie
		// zamykanie okna gry za pomoc� przycisku "X" w prawym g�rnym rogu okna
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			definitive_end = true;
		al_flip_display();
	}

	//zapisanie tabeli wynik�w do pliku tekstowego po zako�czeniu gry przez u�ytkownika
	if (end)
		write_to_file("tabela_wynikow.txt", score_list);

	//usuni�cie wektora przycisk�w
	delete_vector(vector_of_buttons);

	//usuni�cie wektora wektor�w p�l planszy
	pola_planszy.~Board();

	al_destroy_font(ttf_font); //usuni�cie czcionki o wielko�ci 24
	al_destroy_font(big_ttf_font); //usuni�cie czcionki o wielko�ci 128
	al_destroy_event_queue(event_queue); //usuni�cie kolejki zdarze�
	al_destroy_display(main_display); //usuni�cie okna gry
	return 0;
}