#include "Clasificador.h"
#include <string>
#include <iostream>
#include <bitset>
#include <math.h>
#define BYTE_SIZE 8
#define WORD_SIZE 32
using std::cerr;
using std::endl;
using std::string;
using std::ios;
using std::vector;

Clasificador::Clasificador(Packages& packages, File* file_) : 
packages(packages) {
	this->file = file_;
}


void Clasificador::run(){
	// while para leer las tuplas de 4 bytes y guardar tipo, cantidad y 
	// ancho en bitset
	char byte_leido;
	std::bitset<WORD_SIZE> bitset_clasificacion;
	size_t largo_clasificacion = 4; //en bytes
	
	while (true) {
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
		if (this->file->eof()) {
			break;
		}
		
		size_t tipo_tornillo = 0;
		int cont = 0;
		
		for (int k = 4; k >= 0; k--) {
			if (bitset_clasificacion[k]) {
				tipo_tornillo += pow(2, cont);
			}
			cont++;
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
		
		// agrego info a Packages 
		this->packages.add_screws(tipo_tornillo, cant_tornillos, ancho_tornillos, 
		this->file->get_name()); 
	}
}
	
	
