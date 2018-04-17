#include <string>
#include <bitset>
#include <iostream>
#include <math.h>
#include <vector>
#include "File.h"
#include "Paquetes.h"
#define POS_CONFIG_FILE 1
#define OK_FOPEN "se establece conexion con el dispositivo "
#define DELIM_CFG "="
#define DELIM_NOT_ID ","
#define DELIM_CLASIFICADOR '\0'
#define BYTE_SIZE 8
#define WORD_SIZE 32
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
			File clasificador(array_nombre_archivos[i], flags_clasificador);
			
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
			cout << array_nombre_archivos[i] << ": " << OK_FOPEN 
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


File cant_clasificaciones(File file, size_t* cant_clasif) {
	// muevo puntero del File para contar la cantidad de clasificaciones
	// finalmente vuelvo a la posicion actual
	std::ios_base::seekdir end = std::ios::end;
	std::ios_base::seekdir begin = std::ios::beg;
	std::ios_base::seekdir current = std::ios::cur;
	size_t pos_actual = file.tell_g(); 
	file.seek_g(0, end);
	size_t pos_final_archivo = file.tell_g();
	file.seek_g(0, begin);
	file.seek_g(pos_actual, current);
	
	*cant_clasif = (pos_final_archivo - pos_actual) / 4;
	return file; 
}

 
int empaquetador(int largo_array_nombres, char* nombre_archivos[]) {
	std::ios_base::openmode flags_config = ios::in;
	File config(array_nombre_archivos[POS_CONFIG_FILE], flags_config);
	
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
	
	
	vector<thread> threads;
	
	
	
	
	
	
	// encapsular en una clase abstracta (clasificador) con un metodo run 
	// abstracto y sobreescribir el operator()
	// 03 del tuto
	
	char byte_leido;
	// abro y uso clasificadores
	for (unsigned int i = 0; i < files.size(); i++) {
		File clasificador = std::move(files[i]);
		
		size_t cantidad_clasificaciones;
		File clasificador_bis = std::move(cant_clasificaciones(std::move(clasificador), &cantidad_clasificaciones));
		
		// for para leer las tuplas de 4 bytes y guardar tipo, cantidad y 
		// ancho en bitset
		std::bitset<WORD_SIZE> bitset_clasificacion;
		for (size_t i = 0; i < cantidad_clasificaciones; i++) {
			size_t largo_clasificacion = 4; //en bytes
			size_t cont_bits = 0; // para poner los 32 bits en bitset
			for (size_t j = 0; j < largo_clasificacion; j++) {
				clasificador_bis.read(&byte_leido, sizeof(char));
				
				for (size_t l = 0; l < BYTE_SIZE; l++) {
					// 0x80 = 1000 0000
					bitset_clasificacion.set(cont_bits, 
					(bool)((byte_leido << l) & 0x80));
					cont_bits++;
				}
			}
			// aca miro si esta atascado, en ese caso leo la siguiente tupla de
			// 4 bytes
			if (bitset_clasificacion.count() == WORD_SIZE) {
				cerr << clasificador_bis.get_name() << " atascado" << endl;
				continue;
			}
			
			size_t tipo_tornillo = 0;
			
			int cont = 0;
			for (int k = 4; k >= 0; k--) {
				if (bitset_clasificacion[k]) {
					tipo_tornillo += pow(2, cont);
				}
				cont++;
			}
			// verifico que el tipo de tornillo sea valido, en caso contrario
			// leo la siguiente tupla de 4 bytes
			if (!paquetes.is_valid_screw(tipo_tornillo)) {
				cerr << "Tipo de tornillo invalido: " << tipo_tornillo << endl;
				continue;
			}
			
			size_t cant_tornillos = 0;
			size_t ancho_tornillos = 0; 
			
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
			// agrego info a paquetes 
			paquetes.add_screws(tipo_tornillo, cant_tornillos, ancho_tornillos); 
		}
	}
	
	for (int i = 0; i < files.size(); i++) {
		threads[i].join();
	}
	
	
	informe_remanentes(paquetes); //mirar pasaje de objetos
	return OK;
}
