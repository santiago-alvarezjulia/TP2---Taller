#include <iostream>
#include "empaquetador.h"
#define TODO_OK 0
#define ERROR 1
#define CANTIDAD_MINIMA_PARAMETROS 3

int main(int argc, char* argv[]) {
	if (argc < CANTIDAD_MINIMA_PARAMETROS) {
		std::cerr << "Error de parametros" << std::endl;
		return ERROR;
	}
	return empaquetador(argc, argv);
}
