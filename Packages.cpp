#include "Packages.h"
#include "Fprintf_protected.h"
#include <utility>
#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#define BITS_SET_5 31
#define BITS_SET_22 4194303
using std::string;
using std::map;
using std::cout;
using std::endl;
using std::mutex;


Packages::Packages() {
	map<size_t, Screw_Package> paq;
	this->packages = paq;
	map<size_t, std::mutex*> mut;
	this->mutexes = mut;
}


void Packages::add_package(size_t id, string nombre_descriptivo, 
size_t limite_paquete) {
	// para cuando cambio_paquete_lleno
	if (this->mutexes.count(id) == 0) {
		this->mutexes.emplace(id, new std::mutex);
	}
	Screw_Package package(id, nombre_descriptivo, limite_paquete);
	this->packages.insert(std::pair<size_t, Screw_Package> (id, package));
}


void Packages::add_screws(size_t id, size_t cant_tornillos, 
size_t ancho_tornillos, string filename) {
	// verifico que el tipo de tornillo sea valido, en caso contrario
	// leo la siguiente tupla de 4 bytes
	int valid = this->is_valid_screw(id, cant_tornillos, ancho_tornillos);
	if (valid == 1) {
		fprintf_error_invalid_id(id);
		return;
	} else if (valid == 2) {
		fprintf_error_atascado(filename);
		return;
	}
	Lock lock(*this->mutexes.at(id));
	Screw_Package& paquete = this->packages.at(id);
	size_t screws_leftovers = paquete.add_screws(cant_tornillos, 
	ancho_tornillos);
	while (screws_leftovers > 0) {
		cambiar_paquete_lleno(id);
		screws_leftovers = this->packages.at(id).add_screws(
		screws_leftovers, ancho_tornillos);
	}
	
	// para el caso en que justo se llena el paquete y no sobra nigun tornillo
	if (this->packages.at(id).is_package_full()) {
		cambiar_paquete_lleno(id);
	}
}


void Packages::cambiar_paquete_lleno(size_t id) {
	Screw_Package& paquete_lleno = this->packages.at(id);
	size_t capacity = paquete_lleno.get_capacity();
	string descriptive_name = paquete_lleno.get_descriptive_name();
	paquete_lleno.printf_paquete_lleno();
	this->packages.erase(id);
	add_package(id, descriptive_name, capacity);
}


void Packages::printf_remanentes() {
	for (map<size_t, Screw_Package>::iterator it = this->packages.begin(); 
	it != this->packages.end(); ++it) {
		cout << "* " << (it->second).get_screws_inside() 
		<< " tornillos de tipo " << (it->second).get_descriptive_name() << endl;
	}
}


int Packages::is_valid_screw(size_t id, size_t cant_tornillos, 
size_t ancho_tornillos) {
	// agregar verificacion atascado (si esta atascado devuelvo 2)
	if (id == BITS_SET_5 && cant_tornillos == BITS_SET_22 && 
	ancho_tornillos == BITS_SET_5) {
		return 2;
	}
	std::map<size_t, Screw_Package>::iterator it = this->packages.find(id);
	if(it == this->packages.end()) {
		return 1;
	}
	return 0;
}


Packages::~Packages() {
	// delete de los mutex
	for (map<size_t, std::mutex*>::iterator it = this->mutexes.begin(); 
	it != this->mutexes.end(); ++it) {
		delete it->second;
	}
}
