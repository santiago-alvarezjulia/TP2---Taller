#include "Clasificador.h"
#include <string>
#include <iostream>
#include <bitset>
#include <math.h>
#define BYTE_SIZE 8
#define WORD_SIZE 32
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ios;
using std::vector;

Clasificador::Clasificador(Paquetes& packages, File* file_) : 
packages(packages) {
	this->file = std::move(file_);
}


File* Clasificador::cant_clasificaciones(File* file, size_t* cant_clasif) {
	// muevo puntero del File para contar la cantidad de clasificaciones
	// finalmente vuelvo a la posicion actual
	std::ios_base::seekdir end = std::ios::end;
	std::ios_base::seekdir begin = std::ios::beg;
	std::ios_base::seekdir current = std::ios::cur;
	size_t pos_actual = file->tell_g(); 
	file->seek_g(0, end);
	size_t pos_final_archivo = file->tell_g();
	file->seek_g(0, begin);
	file->seek_g(pos_actual, current);
	
	*cant_clasif = (pos_final_archivo - pos_actual) / 4;
	return file; 
}


void Clasificador::run(){
	size_t cantidad_clasificaciones;
	char byte_leido;
	// abro y uso clasificadores
	this->file = std::move(cant_clasificaciones(std::move(this->file), 
	&cantidad_clasificaciones));
		
	// for para leer las tuplas de 4 bytes y guardar tipo, cantidad y 
	// ancho en bitset
	std::bitset<WORD_SIZE> bitset_clasificacion;
	for (size_t i = 0; i < cantidad_clasificaciones; i++) {
		size_t largo_clasificacion = 4; //en bytes
		size_t cont_bits = 0; // para poner los 32 bits en bitset
		for (size_t j = 0; j < largo_clasificacion; j++) {
			this->file->read(&byte_leido, sizeof(char));
			
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
			cerr << this->file->get_name() << " atascado" << endl;
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
		if (!this->packages.is_valid_screw(tipo_tornillo)) {
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
		this->packages.add_screws(tipo_tornillo, cant_tornillos, ancho_tornillos); 
	}
}
	
	
