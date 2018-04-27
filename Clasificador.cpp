#include "Clasificador.h"
#include <string>
#include <iostream>
#include <bitset>
#include <math.h>
#define LEN_CLASIFICATION 4
#define WORD_SIZE 32
#define BYTE_SIZE 8
using std::cerr;
using std::endl;
using std::string;
using std::ios;
using std::vector;
using std::bitset;

Clasificador::Clasificador(Packages& packages, File* file_) : 
packages(packages) {
	this->file = file_;
}


void Clasificador::run(){
	// while para leer las tuplas de 4 bytes y guardar tipo, cantidad y 
	// ancho en bitset
	char byte_leido;
	bitset<WORD_SIZE> bitset_clasificacion;
	bitset<5> id;
	bitset<22> cant_tornillos;
	bitset<5> ancho_tornillos;
	
	while (true) {
		size_t cont_bits = 31; // para poner los 32 bits en bitset
		for (size_t j = 0; j < LEN_CLASIFICATION; j++) {
			this->file->read(&byte_leido, sizeof(char));
			for (size_t l = 0; l < BYTE_SIZE; l++) {
				// 0x80 = 1000 0000
				bitset_clasificacion.set(cont_bits, 
				(bool)((byte_leido << l) & 0x80));
				cont_bits--;
			}
		}
		if (this->file->eof()) {
			break;
		}

		size_t l = 0;
		for (; l < 5; l++) {
			ancho_tornillos.set(l, bitset_clasificacion[l]);
		}
		for (int i = 0; l < 27; l++) {
			cant_tornillos.set(i, bitset_clasificacion[l]);
			i++;
		}
		for (int j = 0; l < 32; l++) {
			id.set(j, bitset_clasificacion[l]);
			j++;
		}
		
		// agrego info a Packages 
		this->packages.add_screws((size_t)id.to_ulong(), 
		(size_t)cant_tornillos.to_ulong(), (size_t)ancho_tornillos.to_ulong(), 
		this->file->get_name()); 
	}
}
	
	
