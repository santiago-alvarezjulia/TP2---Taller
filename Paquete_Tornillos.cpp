#include <cstddef>

class Paquete_Tornillos {
	private:
		std::size_t capacidad;
		std::size_t tornillos_dentro;
		std::size_t* array_ancho_tornillos;
		bool esta_lleno_paquete;
		char* tipo;
	
	public:
		Paquete_Tornillos (char* tipo_paquete, std::size_t capacidad_paquete) {
			this->capacidad = capacidad_paquete;
			this->tornillos_dentro = 0;
			this->esta_lleno_paquete = false;
			this->tipo = tipo_paquete;
			this->array_ancho_tornillos = new std::size_t[capacidad_paquete];
		}
	
		void agregar_tornillo (std::size_t ancho_tornillo) {
			this->array_ancho_tornillos[tornillos_dentro] = ancho_tornillo;
			this->tornillos_dentro++;
			if (this->tornillos_dentro == this->capacidad) {
				this->esta_lleno_paquete = true;
			}
		}
		
		std::size_t get_capacidad() {
			return this->capacidad;
		}
		
		std::size_t get_tornillos_dentro() {
			return this->tornillos_dentro;
		}
		
		char* get_tipo() {
			return this->tipo;
		}
		
		bool esta_lleno() {
			return this->esta_lleno_paquete;
		}
		
		int get_mediana() {
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
