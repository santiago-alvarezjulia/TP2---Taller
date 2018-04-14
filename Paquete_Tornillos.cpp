#include "Paquete_Tornillos.h"
#include <string>
#include <algorithm>
using std::string;

Paquete_Tornillos::Paquete_Tornillos(string id_screw, size_t capacity_) {
	this->capacity = capacity_;
	this->screws_inside = 0;
	this->is_full = false;
	this->id = id_screw;
	std::vector<size_t> vect_screws_width(this->capacity, 0); // capacidad es el largo y 0 el valor inicial
	this->screws_width = vect_screws_width;
}
	
void Paquete_Tornillos::add_screws(size_t screws_quantity, size_t width) {
	for (size_t i = 0; i < screws_quantity; i++) {
		this->screws_width.push_back(width);
	}
	this->screws_inside += screws_quantity;
	if (this->screws_inside == this->capacity) {
		this->is_full = true;
	}
	// ordeno el vector ancho_tornillos
	std::sort(this->screws_width.begin(), this->screws_width.end());
}
		
size_t Paquete_Tornillos::get_capacity() const {
	return this->capacity;
}
		
size_t Paquete_Tornillos::get_screws_inside() const {
	return this->screws_inside;
}
		
string Paquete_Tornillos::get_id() const {
	return this->id;
}
		
bool Paquete_Tornillos::is_package_full() const {
	return this->is_full;
}
		
size_t Paquete_Tornillos::get_mediana() const {
	if ((this->capacity % 2) == 0) {
		// puede que este mal
		return ((this->screws_width[this->capacity / 2] - 1) + 
		(this->screws_width[this->capacity / 2])) / 2;
	}
	return this->screws_width[this->capacity / 2];
}
		
Paquete_Tornillos::~Paquete_Tornillos() {
	//por ahora nada
}
