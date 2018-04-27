#include "Fprintf_protected.h"
#include <iostream>
using std::cerr;
using std::endl;
using std::string;

void fprintf_error_invalid_id(size_t id) {
	cerr << "Tipo de tornillo invalido: " << id << endl;
}

void fprintf_error_atascado(string filename) {
	cerr << filename << " atascado" << endl;
}
