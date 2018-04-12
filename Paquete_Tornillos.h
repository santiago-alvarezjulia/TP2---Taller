#ifndef PAQUETE_TORNILLOS_H
#define PAQUETE_TORNILLOS_H

#include <iostream>

class Paquete_Tornillos {
	size_t capacidad;
	size_t tornillos_dentro;
	size_t* array_ancho_tornillos;
	bool esta_lleno_paquete;
	std::string id_paquete;
	
	public:
		Paquete_Tornillos(std::string id_tornillo, size_t capacidad_paquete);
		void agregar_tornillo (size_t ancho_tornillo);
		size_t get_capacidad ();	
		size_t get_tornillos_dentro ();
		std::string get_id_paquete ();
		bool esta_lleno ();
		int get_mediana ();
		~Paquete_Tornillos();
};

#endif //PAQUETE_TORNILLOS_H
