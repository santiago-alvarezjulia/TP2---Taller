#include <cstdio>
#include <iostream>
#include <fstream>
#include <bitset>
#include <map>
#include <cstdlib>
#include "Paquete_Tornillos.h"
#define ERROR_FOPEN "no se pudo conectar con el dispositivo"
#define OK_FOPEN "se pudo conectar con el dispositivo"
#define DELIM_CFG "="
#define DELIM_NOT_ID ","
#define DELIM_CLASIFICADOR '\0'
#define TAMANIO_BYTE 8
#define TAMANIO_WORD 32
#define ERROR 1
using namespace std;


int empaquetador(int largo_array_nombres, char* array_nombre_archivos[]) {
	fstream config;
	config.open(array_nombre_archivos[1], ios::in);
	if (!config.is_open()) {
		cout << "AAAAA" << endl;
		cerr << array_nombre_archivos[1] << ": " << ERROR_FOPEN << endl;
		return ERROR;
	}
	
	map<string, Paquete_Tornillos> paquetes;
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
		/* // anda mal esta parte, paquete solo vive en este scope
		//creo paquetes (map de string-paquete_tornillos)
		Paquete_Tornillos paquete (id, atoi(limite_paquete.c_str()));
		paquetes.insert(pair<string, Paquete_Tornillos> (id, paquete));
		*/
	}
	config.close();
	
	// abro y uso clasificadores
	string nombre_clasificador;
	string tipo_tornillo;
	string cantidad_tornillos_clasificados;
	string ancho_tornillos_clasificados;
	
	for (int i = 2; i < largo_array_nombres; i++) {
		fstream clasificador;
		clasificador.open(array_nombre_archivos[i], ios::in | ios::binary);
		if (!clasificador.is_open()) {
			cerr << array_nombre_archivos[i] << ": " << ERROR_FOPEN << endl;
			return ERROR;
		}
		
		// do while para sacar el nombre del clasificador. Dejar el seek en el byte separador 0 . No hizo falta hacer swap de bytes
		char byte_leido;
		string nombre_clasificador;
		do {
			clasificador.read(&byte_leido, sizeof(char));
			nombre_clasificador.push_back(byte_leido);
		} while (byte_leido != DELIM_CLASIFICADOR);
		cout << nombre_clasificador << ": " << OK_FOPEN << endl;
		
		
		size_t pos_actual = clasificador.tellg(); //falta un +1?
		clasificador.seekg(0, ios::end);
		size_t pos_final_archivo = clasificador.tellg();
		clasificador.seekg(0, ios::beg);
		clasificador.seekg(pos_actual, ios::cur);
		size_t cantidad_clasificaciones = (pos_final_archivo - pos_actual) / 4; //devuelve 5 para simple42	
		
		
		// for para leer las tuplas de 4 bytes y guardar tipo, cantidad y ancho en bitset
		bitset<TAMANIO_WORD> bitset_clasificacion; 
		string bits;
		for (size_t i = 0; i < cantidad_clasificaciones; i++) {
			size_t largo_clasificacion = 4; //en bytes
			size_t cont_bits = 0; // para poner los 32 bits de una en bitset_clasificacion
			for (size_t j = 0; j < largo_clasificacion; j++) {
				clasificador.read(&byte_leido, sizeof(char));
				// swap byte (endianess)
				// convertir de byte (char) a bits(puede ser a string o agregar directo a bitset)
				for (size_t l = 0; l < TAMANIO_BYTE; l++) {
					bitset_clasificacion[cont_bits] = bits[l];
					cout << bitset_clasificacion.test(cont_bits) << endl; //debug
					cont_bits++;
				}
			}
			// separar en 5, 22 y 5
			// pasar bits a int
			// agregar info a paquetes almacenados en el map
		}
		
		
		clasificador.close();
	}
	return 0;
}
