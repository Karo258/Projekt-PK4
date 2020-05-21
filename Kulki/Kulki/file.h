#pragma once

#include <string>
#include "list.h"

void read_from_file(std::string filename, lista* moja_lista);

void write_to_file(std::string filename, lista* & moja_lista);