#include "Fprintf_protected.h"
#include "Lock.h"
#include <iostream>
#include <string>
using std::cerr;
using std::endl;
using std::string;

Fprintf_protected::Fprintf_protected() {}

void Fprintf_protected::fprintf_error_invalid_id(size_t id) {
	Lock lock(this->mutex);
	cerr << "Tipo de tornillo invalido: " << id << endl;
}


void Fprintf_protected::fprintf_error_atascado(string filename) {
	Lock lock(this->mutex);
	cerr << filename << " atascado" << endl;
}

Fprintf_protected::~Fprintf_protected() {}
