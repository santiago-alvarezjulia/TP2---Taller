#include <iostream>
#include "Empaquetador.h"
#define ERROR 1
#define OK 0
#define CANTIDAD_MINIMA_PARAMETROS 3

int main(int argc, char* argv[]) {
	if (argc < CANTIDAD_MINIMA_PARAMETROS) {
		std::cerr << "Error de parametros" << std::endl;
		return ERROR;
	}
	Empaquetador empaquetador(argc, argv);
	empaquetador.set_config();
	empaquetador.set_clasification_files();
	int ret = empaquetador.empaquetar();
	if (ret == OK) {
		empaquetador.informe_remanentes();
	}
	return ret; 
}
