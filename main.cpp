#include <iostream>
#include "empaquetador.h"
#define TODO_OK 0
#define ERROR 1
#define CANTIDAD_MINIMA_PARAMETROS 3
using namespace std;

int main (int argc, char* argv[]) {
	if (argc < CANTIDAD_MINIMA_PARAMETROS) {
		cerr << "Error de parametros" << endl;
		return ERROR;
	}
	return empaquetador(argc, argv);
}
