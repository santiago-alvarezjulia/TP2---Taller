#include <string>
#include <iostream>
#include <vector>
#include "File.h"
#include "Paquetes.h"
#include "Thread.h"
#include "Clasificador.h"
#define POS_CONFIG_FILE 1
#define OK_FOPEN "se establece conexion con el dispositivo "
#define DELIM_CFG "="
#define DELIM_NOT_ID ","
#define DELIM_CLASIFICADOR '\0'
#define ERROR 1
#define OK 0
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ios;
using std::vector;
using std::thread;


vector<File> open_files(int largo_array_nombres, char* nombre_archivos[]) {
	vector<File> files_vector;
	for (int i = 2; i < largo_array_nombres; i++) {
		std::ios_base::openmode flags_clasificador = 
		std::ios::in | std::ios::binary;
		File clasificador(nombre_archivos[i], flags_clasificador);
		
		// me fijo si hubo error al intentar abrir el archivo
		if (clasificador.fail_open()) {
			continue;
		} 
		char byte_leido;
		// do while para sacar el nombre del clasificador
		string nombre_clasificador;
		while (true) {
			clasificador.read(&byte_leido, sizeof(char));
			if (byte_leido == DELIM_CLASIFICADOR) {
				break;
			}
			nombre_clasificador.push_back(byte_leido);
		}
		// me pude conectar con el dispositivo
		cout << nombre_archivos[i] << ": " << OK_FOPEN 
		<< nombre_clasificador << endl;
		clasificador.set_name(nombre_clasificador);
		files_vector.push_back(std::move(clasificador));
	}
	return files_vector;
}

void informe_remanentes(Paquetes packages) {
	// se ordenan por el numero de tipo
	cout << "# Informe de remanentes" << endl;
	packages.printf_remanentes();
}

 
int empaquetador(int largo_array_nombres, char* nombre_archivos[]) {
	std::ios_base::openmode flags_config = ios::in;
	File config(nombre_archivos[POS_CONFIG_FILE], flags_config);
	
	Paquetes paquetes;
	string line;
	string id;
	string nombre_descriptivo;
	string limite_paquete;
	
	while (!config.eof()) {
		config.get_line(line);
		// para el caso el que el eof se encuentra en una linea "vacia"
		if (line.empty()) {
			break;
		}

		size_t index_delim_cfg = line.find(DELIM_CFG);
		id = line.substr(0, index_delim_cfg);

		line = line.substr(index_delim_cfg + 1); //el 1 es el largo del delim
		size_t index_delim_not_id = line.find(DELIM_NOT_ID);
		nombre_descriptivo = line.substr(0, index_delim_not_id);

		limite_paquete = line.substr(index_delim_not_id + 1);

		paquetes.add_package((size_t)atoi(id.c_str()), nombre_descriptivo, 
		(size_t)atoi(limite_paquete.c_str()));
	}
	
	vector<File> files = open_files(largo_array_nombres, nombre_archivos);
	vector<Thread*> threads;
	
	for (size_t i = 0; i < files.size(); i++) {
		threads.push_back(new Clasificador(paquetes, std::move(&files[i])));
	}
	
	
	for (size_t i = 0; i < files.size(); i++) {
		threads[i]->start();
	}
	

	for (size_t i = 0; i < files.size(); i++) {
		threads[i]->join();
		delete threads[i];
	}
	
	informe_remanentes(paquetes);
	return OK;
}
