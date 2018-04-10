#include "Paquete_Tornillos.h"
#include <cstddef>
#include <iostream>
using namespace std;

class Paquete_Tornillos {
	private:
		size_t capacidad;
		size_t tornillos_dentro;
		size_t* array_ancho_tornillos;
		bool esta_lleno_paquete;
		string id_paquete;
	
	public:
		Paquete_Tornillos (string id_tornillo, size_t capacidad_paquete) {
			this->capacidad = capacidad_paquete;
			this->tornillos_dentro = 0;
			this->esta_lleno_paquete = false;
			this->id_paquete = id_tornillo;
			this->array_ancho_tornillos = new size_t[capacidad_paquete];
		}
	
		void agregar_tornillo (size_t ancho_tornillo) {
			this->array_ancho_tornillos[tornillos_dentro] = ancho_tornillo;
			this->tornillos_dentro++;
			if (this->tornillos_dentro == this->capacidad) {
				this->esta_lleno_paquete = true;
			}
		}
		
		size_t get_capacidad () {
			return this->capacidad;
		}
		
		size_t get_tornillos_dentro () {
			return this->tornillos_dentro;
		}
		
		string get_id_paquete () {
			return this->id_paquete;
		}
		
		bool esta_lleno () {
			return this->esta_lleno_paquete;
		}
		
		int get_mediana () {
			if ((this->capacidad % 2) == 0) {
				// puede que este mal
				return ((this->array_ancho_tornillos[this->capacidad / 2] - 1) + (this->array_ancho_tornillos[this->capacidad / 2])) / 2 ;
			}
			return this->array_ancho_tornillos[this->capacidad / 2];
		}
		
		~Paquete_Tornillos() {
			delete[] this->array_ancho_tornillos;
		}
}; 
