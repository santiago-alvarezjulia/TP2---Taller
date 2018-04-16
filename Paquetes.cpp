#include "Paquetes.h"
#include "Paquete_Tornillos.h"
#include <map>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <string>
using std::string;
using std::map;
using std::cout;
using std::endl;


Paquetes::Paquetes() {
	map<size_t, Paquete_Tornillos> paq;
	this->paquetes = paq;
}


void Paquetes::add_package(size_t id, string nombre_descriptivo, 
size_t limite_paquete) {
	Paquete_Tornillos package(id, nombre_descriptivo, limite_paquete);
	this->paquetes.insert(std::pair<size_t, Paquete_Tornillos> (id, package));
}


void Paquetes::add_screws(size_t tipo_tornillo, size_t cant_tornillos, 
size_t ancho_tornillos) {
	Paquete_Tornillos& paquete = this->paquetes.at(tipo_tornillo);
	size_t screws_leftovers = paquete.add_screws(cant_tornillos, 
	ancho_tornillos);
	while (screws_leftovers > 0) {
		cambiar_paquete_lleno(tipo_tornillo);
		screws_leftovers = this->paquetes.at(tipo_tornillo).add_screws(
		screws_leftovers, ancho_tornillos);
	}
	
	// para el caso en que justo se llena el paquete y no sobra nigun tornillo
	if (this->paquetes.at(tipo_tornillo).is_package_full()) {
		cambiar_paquete_lleno(tipo_tornillo);
	}
}


void Paquetes::cambiar_paquete_lleno(size_t id) {
	Paquete_Tornillos& paquete_lleno = this->paquetes.at(id);
	size_t capacity = paquete_lleno.get_capacity();
	string descriptive_name = paquete_lleno.get_descriptive_name();
	paquete_lleno.printf_paquete_lleno();
	this->paquetes.erase(id);
	add_package(id, descriptive_name, capacity);
}


void Paquetes::printf_remanentes() {
	for (map<size_t, Paquete_Tornillos>::iterator it = this->paquetes.begin(); 
	it != this->paquetes.end(); ++it) {
		cout << "* " << (it->second).get_screws_inside() 
		<< " tornillos de tipo " << (it->second).get_descriptive_name() << endl;
	}
}


bool Paquetes::is_valid_screw(size_t id) {
	return this->paquetes.count(id) != 0;
}


Paquetes::~Paquetes() {
	//por ahora nada
}
