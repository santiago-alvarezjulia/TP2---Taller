#include <stdio.h>
#include <iostream>
#include <string>
#define TODO_OK 0
#define ERROR 1
#define ERROR_FOPEN "no se pudo conectar con el dispositivo"
#define OK_FOPEN "se pudo conectar con el dispositivo"
#define CFG ".cfg"
#define CANTIDAD_MINIMA_PARAMETROS 3

int empaquetador(int largo_array_nombres, char* array_nombre_archivos[]);


int main (int argc, char* argv[]) {
	if (argc < CANTIDAD_MINIMA_PARAMETROS) {
		fprintf(stderr, "Error de parametros");
		return ERROR;
	}
	return empaquetador(argc, argv);
}
