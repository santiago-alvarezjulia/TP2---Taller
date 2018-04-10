#include <cstdio>
#include "empaquetador.h"
#define TODO_OK 0
#define ERROR 1
#define CANTIDAD_MINIMA_PARAMETROS 3

int main (int argc, char* argv[]) {
	if (argc < CANTIDAD_MINIMA_PARAMETROS) {
		fprintf(stderr, "Error de parametros");
		return ERROR;
	}
	return empaquetador(argc, argv);
}
