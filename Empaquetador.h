#ifndef EMPAQUETADOR_H
#define EMPAQUETADOR_H

#include "Thread.h"
#include "Packages.h"
#include "File.h"
#include <vector>

class Empaquetador {
	std::vector<File> files;
	Packages packages;
	char** filename_array;
	std::vector<File> open_files(int largo_array_nombres, char* nombre_archivos[]);
	
	public:
		Empaquetador(int largo_array_nombres, char* nombre_archivos[]);
		void set_config();
		void set_clasification_files();
		int empaquetar();
		void informe_remanentes();
		~Empaquetador();
};

#endif // EMPAQUETADOR_H
