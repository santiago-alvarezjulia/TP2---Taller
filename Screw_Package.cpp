#include "Screw_Package.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using std::string;
using std::vector;


Screw_Package::Screw_Package(size_t id_screw, string name, size_t capacity_) {
	this->capacity = capacity_;
	this->screws_inside = 0;
	this->is_full = false;
	this->id = id_screw;
	this->descriptive_name = name;
	vector<size_t> vect_screws_width;
	this->screws_width = vect_screws_width;
}

	
size_t Screw_Package::add_screws(size_t screws_quantity, size_t width) {
	size_t screws_to_add = screws_quantity;
	size_t available_space = this->capacity - this->screws_inside;
	if (screws_quantity >= available_space) {
		screws_to_add = available_space;
		this->is_full = true;
	}
	// agrego ancho tornillos al vector ancho_tornillos
	for (size_t i = 0; i < screws_to_add; i++) {
		this->screws_width.push_back(width);
	}
	// agrego la cantidad de tornillos
	this->screws_inside += screws_to_add;

	// ordeno el vector ancho_tornillos
	std::sort(this->screws_width.begin(), this->screws_width.end());
	return screws_quantity - screws_to_add;
}

		
size_t Screw_Package::get_capacity() const {
	return this->capacity;
}

		
size_t Screw_Package::get_screws_inside() const {
	return this->screws_inside;
}

		
size_t Screw_Package::get_id() const {
	return this->id;
}


string Screw_Package::get_descriptive_name() const {
	return this->descriptive_name;
}

		
bool Screw_Package::is_package_full() const {
	return this->is_full;
}

		
size_t Screw_Package::get_mediana() const {
	if ((this->capacity % 2) == 0) {
		return ((this->screws_width[(this->capacity / 2) - 1]) + 
		(this->screws_width[this->capacity / 2])) / 2;
	}
	return this->screws_width[this->capacity / 2];
}


void Screw_Package::printf_paquete_lleno() {
	std::cout << "Paquete listo: " << get_screws_inside() 
	<< " tornillos de tipo " << this->descriptive_name << " (mediana: " 
	<< get_mediana() << ")" << std::endl;
} 

	
Screw_Package::~Screw_Package() {}
