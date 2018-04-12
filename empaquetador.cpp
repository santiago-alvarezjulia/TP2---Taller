#include <cstdio>
#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdlib>
#include "Paquete_Tornillos.h"
#define ERROR_FOPEN "no se pudo conectar con el dispositivo"
#define OK_FOPEN "se pudo conectar con el dispositivo"
#define DELIM_CFG "="
#define DELIM_NOT_ID ","
#define DELIM_CLASIFICADOR "\0"
#define TAMANIO_BYTE 8
#define TAMANIO_WORD 32
#define ERROR 1
using namespace std;

void bytes_to_bits(string byte, unsigned char* bits) {
	unsigned char mascara = 1;
	for (int i = 0; i < TAMANIO_BYTE; i++) {
		bits[i] =  (byte & (mascara << i)) != 0;
	}
}

int empaquetador(int largo_array_nombres, char* array_nombre_archivos[]) {
	fstream config;
	config.open(array_nombre_archivos[0], ios::in);
	if (!config.is_open()) {
		cerr << array_nombre_archivos[0] << ": " << ERROR_FOPEN << endl;
		return ERROR;
	}
	
	string linea;
	string id;
	string nombre_descriptivo;
	string limite_paquete;
	
	while (!config.eof()) {
		getline(config, linea);
		size_t index_delim_cfg = linea.find(DELIM_CFG);
		id = linea.substr(0, index_delim_cfg);
		
		linea = linea.substr(index_delim_cfg + 1); //el 1 es el largo del delim
		size_t index_delim_not_id = linea.find(DELIM_NOT_ID);
		nombre_descriptivo = linea.substr(0, index_delim_not_id);
		limite_paquete = linea.substr(index_delim_not_id + 1);
		
		//crear paquete (array de paquetes?)
	}
	config.close();
	
	// abro y uso clasificadores
	string nombre_clasificador;
	string tipo_tornillo;
	string cantidad_tornillos_clasificados;
	string ancho_tornillos_clasificados;
	
	for (int i = 1; i < largo_array_nombres; i++) {
		fstream clasificador;
		clasificador.open(array_nombre_archivos[i], ios::in | ios::binary);
		if (!clasificador.is_open()) {
			cerr << array_nombre_archivos[i] << ": " << ERROR_FOPEN << endl;
			return ERROR;
		}
		
		// while para sacar el nombre del clasificador. Dejar el seek en el byte separador 0 
		string byte_leido;
		string nombre_clasificador;
		
		while (byte_leido != DELIM_CLASIFICADOR) {
			clasificador.read((char*) &byte_leido, sizeof(char));
			//swap byte
			nombre_clasificador.push_back((char) (int)strtol(byte_leido.c_str(), NULL, 16));
		}
		
		
		size_t pos_actual = clasificador.tellg();
		clasificador.seekg(0, ios::end);
		size_t pos_final_archivo = clasificador.tellg();
		clasificador.seekg(0, ios::beg);
		clasificador.seekg(pos_actual, ios::cur);
		size_t cantidad_clasificaciones = (pos_final_archivo - pos_actual) / 4; //revisar
		
		
		// for para leer las tuplas de 4 bytes y guardar tipo, cantidad y ancho en bitset
		bitset<TAMANIO_WORD> bitset_clasificacion; 
		unsigned char bits[TAMANIO_BYTE];
		for (size_t i = 0; i < cantidad_clasificaciones; i++) {
			size_t largo_clasificacion = 4; //en bytes
			size_t cont_bits = 0; // para poner los 32 bits de una en bitset_clasificacion
			for (size_t j = 0; j < largo_clasificacion; j++) {
				clasificador.read((char*) &byte_leido, sizeof(char));
				// swap byte (endianess)
				bytes_to_bits(byte_leido, bits);
				for (size_t l = 0; l < TAMANIO_BYTE; l++) {
					bitset_clasificacion[cont_bits] = bits[l];
					cont_bits++;
				}
			}
			// separar en 5, 22 y 5
			// pasar bits a int
			// agregar info a paquetes
		}
		
		
		clasificador.close();
	}
	return 0;
}
