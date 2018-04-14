#include <string>
#include <bitset>
#include <iostream>
#include <map>
#include <math.h>
#include "Paquete_Tornillos.h"
#include "File.h"
#define ERROR_FOPEN "no se pudo conectar con el dispositivo"
#define OK_FOPEN "se pudo conectar con el dispositivo "
#define DELIM_CFG "="
#define DELIM_NOT_ID ","
#define DELIM_CLASIFICADOR '\0'
#define TAMANIO_BYTE 8
#define TAMANIO_WORD 32
#define ERROR 1
#define TODO_OK 0
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ios;


int empaquetador(int largo_array_nombres, char* array_nombre_archivos[]) {
	std::ios_base::openmode flags_config = ios::in;
	File config (array_nombre_archivos[1], flags_config);
	
	std::map<string, Paquete_Tornillos> paquetes;
	string line;
	string id;
	string nombre_descriptivo;
	string limite_paquete;
	
	while (!config.eof()) {
		config.get_line(line);

		size_t index_delim_cfg = line.find(DELIM_CFG);
		id = line.substr(0, index_delim_cfg);

		line = line.substr(index_delim_cfg + 1); //el 1 es el largo del delim
		size_t index_delim_not_id = line.find(DELIM_NOT_ID);
		nombre_descriptivo = line.substr(0, index_delim_not_id);

		limite_paquete = line.substr(index_delim_not_id + 1);
		/* // anda mal esta parte, paquete solo vive en este scope
		 * // creo q esta explicado en movimiento de objetos .pdf
		//creo paquetes (map de string-paquete_tornillos)
		Paquete_Tornillos paquete (id, atoi(limite_paquete.c_str()));
		paquetes.insert(pair<string, Paquete_Tornillos> (id, paquete));
		*/
	}
	
	// abro y uso clasificadores
	for (int i = 2; i < largo_array_nombres; i++) {
		std::ios_base::openmode flags_clasificador = 
		std::ios::in | std::ios::binary;
		File clasificador (array_nombre_archivos[i], flags_clasificador);
		
		char byte_leido;
		
		// do while para sacar el nombre del clasificador
		string nombre_clasificador;
		do {
			clasificador.read(&byte_leido, sizeof(char));
			nombre_clasificador.push_back(byte_leido);
		} while (byte_leido != DELIM_CLASIFICADOR);
		cout << array_nombre_archivos[i] << ": " << OK_FOPEN 
		<< nombre_clasificador << endl;
		
		// muevo puntero del File para contar la cantidad de clasificaciones
		std::ios_base::seekdir end = std::ios::end;
		std::ios_base::seekdir begin = std::ios::beg;
		std::ios_base::seekdir current = std::ios::cur;
		size_t pos_actual = clasificador.tell_g(); //falta un +1?
		clasificador.seek_g(0, end);
		size_t pos_final_archivo = clasificador.tell_g();
		clasificador.seek_g(0, begin);
		clasificador.seek_g(pos_actual, current);
		size_t cantidad_clasificaciones = (pos_final_archivo - pos_actual) / 4; //devuelve 5 para simple42	
		
		// for para leer las tuplas de 4 bytes y guardar tipo, cantidad y ancho en bitset
		std::bitset<TAMANIO_WORD> bitset_clasificacion;
		for (size_t i = 0; i < cantidad_clasificaciones; i++) {
			size_t largo_clasificacion = 4; //en bytes
			size_t cont_bits = 0; // para poner los 32 bits en bitset
			for (size_t j = 0; j < largo_clasificacion; j++) {
				clasificador.read(&byte_leido, sizeof(char));
				
				for (size_t l = 0; l < TAMANIO_BYTE; l++) {
					// 0x80 = 1000 0000
					bitset_clasificacion.set(cont_bits, 
					(bool)((byte_leido << l) & 0x80));
					cont_bits++;
				}
			}
			// aca mira si esta atascado
			if (bitset_clasificacion.count() == TAMANIO_WORD) {
				cerr << nombre_clasificador << " atascado" << endl;
				break;
			}
			
			size_t tipo_tornillo = 0;
			size_t cant_tornillos = 0;
			size_t ancho_tornillos = 0; 
			
			int cont = 0;
			for (int k = 4; k >= 0; k--) {
				if (bitset_clasificacion[k]) {
					tipo_tornillo += pow(2, cont);
				}
				cont++;
			}
			// verificar que el tipo de tornillo sea valido
			// if tipo no pertenece como key al map de paquetes, no es valido
			
			cont = 0;
			for (size_t k = 26; k > 4; k--) {
				if (bitset_clasificacion[k]) {
					cant_tornillos += pow(2, cont);
				}
				cont++;
			}
			
			cont = 0;
			for (size_t k = 31; k > 26; k--) {
				if (bitset_clasificacion[k]) {
					ancho_tornillos += pow(2, cont);
				}
				cont++;
			}

			// agregar info a paquetes almacenados en el map
		}
	}
	return TODO_OK;
}
