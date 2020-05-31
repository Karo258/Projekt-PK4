#pragma once

#include <string>
#include "list.h"

//funkcja realizuj¹ca odczyt z pliku do zaimplementowanej przeze mnie listy jednokierunkowej
void read_from_file(std::string filename, lista* moja_lista);

//funkcja realizuj¹ca zapis do pliku z zaimplementowanej przeze mnie listy jednokierunkowej
void write_to_file(std::string filename, lista* & moja_lista);