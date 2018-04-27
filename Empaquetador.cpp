#include "Empaquetador.h"
#include "File.h"
#include "Packages.h"
#include "Thread.h"
#include "Clasificador.h"
#include <string>
#include <iostream>
#include <vector>
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


Empaquetador::Empaquetador(int len_filename_array, char* filename_array[]) {
	this->files = open_files(len_filename_array, filename_array);
	Packages pack;
	this->packages = pack;
	this->filename_array = filename_array;
}


vector<File> Empaquetador::open_files(int largo_array_nombres, 
char* nombre_archivos[]) {
	vector<File> files_vector;
	
	std::ios_base::openmode flags_config = ios::in;
	File config(nombre_archivos[1], flags_config);
	files_vector.push_back(std::move(config));
	
	for (int i = 2; i < largo_array_nombres; i++) {
		std::ios_base::openmode flags_clasificador = ios::in | ios::binary;
		File clasificador(nombre_archivos[i], flags_clasificador);
		
		// me fijo si hubo error al intentar abrir el archivo
		if (clasificador.fail_open()) {
			continue;
		}
		clasificador.set_name(nombre_archivos[i]);
		files_vector.push_back(std::move(clasificador));
	}
	return files_vector;
}


void Empaquetador::set_config() {
	string line;
	string id;
	string nombre_descriptivo;
	string limite_paquete;
	
	while (!this->files[0].eof()) {
		this->files[0].get_line(line);
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

		this->packages.add_package((size_t)atoi(id.c_str()), nombre_descriptivo, 
		(size_t)atoi(limite_paquete.c_str()));
	}
}


void Empaquetador::set_clasification_files() {
	for (unsigned int i = 1; i < this->files.size(); i++) {
		char byte_leido;
		// do while para sacar el nombre del clasificador
		string nombre_clasificador;
		while (true) {
			this->files[i].read(&byte_leido, sizeof(char));
			if (byte_leido == DELIM_CLASIFICADOR) {
				break;
			}
			nombre_clasificador.push_back(byte_leido);
		}
		// me pude conectar con el dispositivo
		cout << this->files[i].get_name() << ": " << OK_FOPEN 
		<< nombre_clasificador << endl;
		// cambio el nombre del archivo .bin por el que esta dentro del archivo
		this->files[i].set_name(nombre_clasificador);
	}
}


void Empaquetador::informe_remanentes() {
	// se ordenan por el numero de tipo
	cout << "# Informe de remanentes" << endl;
	this->packages.printf_remanentes();
}

 
int Empaquetador::empaquetar() {
	vector<Thread*> threads;
	
	for (size_t i = 1; i < this->files.size(); i++) {
		threads.push_back(new Clasificador(this->packages, 
		std::move(&this->files[i])));
	}
	
	for (size_t i = 0; i < threads.size(); i++) {
		threads[i]->start();
	}
	
	for (size_t i = 0; i < threads.size(); i++) {
		threads[i]->join();
		delete threads[i];
	}
	return OK;
}

Empaquetador::~Empaquetador() {}
