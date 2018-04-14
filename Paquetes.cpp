#include "Paquetes.h"
#include "Paquete_Tornillos.h"
#include <cstdlib>

Paquetes::Paquetes() {
	std::map<string, Paquete_Tornillos> paq;
	this->paquetes = paq;
}


void Paquetes::agregar_paquete(string id, std::string limite_paquete) {
	Paquete_Tornillos paquete (id, atoi(limite_paquete.c_str())); //rompe. move semantics
	this->paquetes.insert(std::pair<string, Paquete_Tornillos> (id, paquete));
}

void Paquetes::agregar_tornillos(string tipo_tornillo, size_t cant_tornillos, 
size_t ancho_tornillos) {
	//Paquete_Tornillos paquete = this->paquetes[tipo_tornillo];
	//paquete.agregar_tornillos(cant_tornillos, ancho_tornillos);
}

Paquetes::~Paquetes() {

}
