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
	al_set_window_title(main_display, "KULKI"); //zatytu�owanie okna gry
	al_clear_to_color(al_map_rgb(30, 110, 125)); //ustawienie koloru t�a okna gry

	
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
	al_get_mouse_state(&mouse);
	al_set_system_mouse_cursor(main_display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_show_mouse_cursor(main_display);

	//utworzenie kolejki zdarze�
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(main_display));	//ustawienie okna gry jako �r�d�a zdarze�
	al_register_event_source(event_queue, al_get_mouse_event_source());	//ustawienie myszy jako �r�d�a zdarze�

	//utworzenie czcionek
	ALLEGRO_FONT* ttf_font = al_load_ttf_font("arial.ttf", 24, 0);	//o wielko�ci 24
	ALLEGRO_FONT* big_ttf_font = al_load_ttf_font("arial.ttf", 128, 0); // o wielko�ci 128

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
	std::vector<std::vector<Field*>> pola_planszy;
	for (int i = 1; i < 9; i++)
	{
		std::vector<Field*>tmp;
		for (int j = 1; j < 9; j++)
		{
			tmp.push_back(new Field(i * 70, j * 70));
		}
		pola_planszy.push_back(tmp);
	}

	//wynik na pocz�tku dzia�ania programu
	const char* twoj_wynik = "0 0 0";
	al_draw_text(big_ttf_font, al_map_rgb(0, 0, 0), 890, 280, 0, twoj_wynik);
	
	//utworzenie jednokierunkowej listy wynik�w
	lista* score_list = new lista();

	//wczytanie wynik�w z pliku do listy jednokierukowej
	read_from_file("tabela_wynikow.txt", score_list);
	char* najwyzszy_wynik = new char[score_list->pierwszy_element().length()+1];
	std::strcpy(najwyzszy_wynik, score_list->pierwszy_element().c_str());
	al_draw_text(big_ttf_font, al_map_rgb(0, 0, 0), 890, 480, 0, najwyzszy_wynik);
	
	//stworzenie wektora nadchodz�cych kulek
	std::vector<Ball*> balls;

	bool end = false; //zmienna lokalna przechowuj�ca warunek g��wnej p�tli programu
	srand(time(NULL));
	while (!end) //g��wna p�tla programu
	{
		//wyrysowanie przycisk�w
		for (int i = 0; i < vector_of_buttons.size(); i++)
			vector_of_buttons[i]->draw();
		
		//zmiana przycisku po najechaniu na niego mysz�
		for (int i = 0; i < vector_of_buttons.size(); i ++)
		{
			bool covered = vector_of_buttons[i]->is_mouse_over();
			if (covered == true)
				i = vector_of_buttons.size();
		}

		//wywo�anie akcji zwi�zanych z przyciskami
		for (int i = 0; i < vector_of_buttons.size(); i++)
		{
			bool  clicked = vector_of_buttons[i]->is_mouse_clicked(end);
			if (clicked)
				i = vector_of_buttons.size();
		}

		//wyrysowanie planszy
		for (int i = 0; i < pola_planszy.size(); i++)
			for (int j = 0; j < pola_planszy[i].size(); j++)
				pola_planszy[i][j]->draw();

		//zmiana pola planszy po najechaniu na nie mysz�
		for (int i = 0; i < pola_planszy.size(); i++)
		{
			bool covered = false;
			for (int j = 0; j < pola_planszy[i].size(); j++)
			{
				covered = pola_planszy[i][j]->is_mouse_over();
				if (covered)
					j = pola_planszy[i].size();
			}
			if (covered)
				i = pola_planszy.size();
		}

		//losowanie kulek do kolejnej rundy
		for (int i = 0; i < 3; i++)
		{
			int x;
			int tmp = rand() % 4;
			if (i == 0)
				x = 913;
			else if (i == 1)
				x = 1035;
			else
				x = 1158;
			switch (tmp)
			{
			case 0:
			{
				balls.push_back(new Ball(x, 150, al_map_rgb(255, 0, 0), 40));
				break;
			}
			case 1:
			{
				balls.push_back(new Ball(x, 150, al_map_rgb(0, 0, 255), 40));
				break;
			}
			case 2:
			{
				balls.push_back(new Ball(x, 150, al_map_rgb(0, 255, 0), 40));
				break;
			}
			case 3:
			{
				balls.push_back(new Ball(x, 150, al_map_rgb(255, 255, 0), 40));
				break;
			}
			}
			
		}
		
		//wyrysowanie nadchodz�cych kulek
		for (int i = 0; i < balls.size(); i++)
			balls[i]->draw();

		//wyrysowanie kulek w losowych miejscach na planszy
		for (int i = 0; i < balls.size(); i++)
		{
			int row = rand() % 8;
			int column = rand() % 8;
			while (pola_planszy[row][column]->is_full() == true)
			{
				row = rand() % 8;
				column = rand() % 8;
			}
			balls[i]->change_coordinates(105 + (row * 70), 105 + (column) * 70, 20);
			balls[i]->draw();
			pola_planszy[row][column]->set_full();
		}

		ALLEGRO_EVENT event;	//utworzenie zdarzenia
		al_wait_for_event(event_queue, &event);	//oczekiwanie na zdarzenie

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)	//zamykanie okna gry za pomoc� przycisku "X" w prawym g�rnym rogu okna
			end = true;

		al_flip_display();

		//usuni�cie element�w wektora przechowuj�cego kulki
		for (int i = balls.size(); i > 0; i--)
			balls.pop_back();

		//zapisanie tabeli wynik�w do pliku tekstowego po zako�czeniu gry przez u�ytkownika
		if (end)
		{
			write_to_file("tabela_wynikow.txt", score_list);
		}
	}

	//usuni�cie wektora przycisk�w
	delete_vector(vector_of_buttons);

	//usuni�cie wektora wektor�w p�l planszy
	for (int i = pola_planszy.size(); i==0; i++)
		delete_vector(pola_planszy[i]);
	
	al_destroy_font(ttf_font); //usuni�cie czcionki o wielko�ci 24
	al_destroy_font(big_ttf_font); //usuni�cie czcionki o wielko�ci 128
	al_destroy_event_queue(event_queue); //usuni�cie kolejki zdarze�
	al_destroy_display(main_display); //usuni�cie okna gry
	return 0;
}