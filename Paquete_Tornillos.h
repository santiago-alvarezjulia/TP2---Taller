#ifndef PAQUETE_TORNILLOS_H
#define PAQUETE_TORNILLOS_H

#include <string>
using std::string;

class Paquete_Tornillos {
	size_t capacidad;
	size_t tornillos_dentro;
	size_t* array_ancho_tornillos; //cambiar por array o vector para poder ordenar y calcular mediana
	bool esta_lleno_paquete;
	string id_paquete;
	
	public:
		Paquete_Tornillos(string id_tornillo, size_t capacidad_paquete);
		void agregar_tornillo(size_t ancho_tornillo);
		size_t get_capacidad() const;	
		size_t get_tornillos_dentro() const;
		string get_id_paquete() const;
		bool esta_lleno() const;
		int get_mediana() const;
		~Paquete_Tornillos();
};

#endif //PAQUETE_TORNILLOS_H
