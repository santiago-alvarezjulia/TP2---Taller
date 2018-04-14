#include "Paquete_Tornillos.h"
#include <string>
using std::string;

Paquete_Tornillos::Paquete_Tornillos(string id_tornillo, 
size_t capacidad_paquete) {
	this->capacidad = capacidad_paquete;
	this->tornillos_dentro = 0;
	this->is_full = false;
	this->id = id_tornillo;
	this->array_ancho_tornillos = new size_t[capacidad_paquete];
}
	
void Paquete_Tornillos::agregar_tornillos(size_t cant_tornillos, size_t ancho_tornillo) {
	this->array_ancho_tornillos[tornillos_dentro] = ancho_tornillo;
	this->tornillos_dentro += cant_tornillos;
	if (this->tornillos_dentro == this->capacidad) {
		this->is_full = true;
	}
}
		
size_t Paquete_Tornillos::get_capacidad() const {
	return this->capacidad;
}
		
size_t Paquete_Tornillos::get_tornillos_dentro() const {
	return this->tornillos_dentro;
}
		
string Paquete_Tornillos::get_id() const {
	return this->id;
}
		
bool Paquete_Tornillos::esta_lleno() const {
	return this->is_full;
}
		
int Paquete_Tornillos::get_mediana() const {
	if ((this->capacidad % 2) == 0) {
		// puede que este mal
		return ((this->array_ancho_tornillos[this->capacidad / 2] - 1) + 
		(this->array_ancho_tornillos[this->capacidad / 2])) / 2;
	}
	return this->array_ancho_tornillos[this->capacidad / 2];
}
		
Paquete_Tornillos::~Paquete_Tornillos() {
	delete[] this->array_ancho_tornillos;
}
