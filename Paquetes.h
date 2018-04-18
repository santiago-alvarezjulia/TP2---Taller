#ifndef PAQUETES_H
#define PAQUETES_H

#include <map>
#include <string>
#include <mutex>
#include "Paquete_Tornillos.h"
#include "Lock.h"
using std::string;

class Paquetes {
	std::map<size_t, Paquete_Tornillos> paquetes;
	std::map<size_t, std::mutex*> mutexes;
	void cambiar_paquete_lleno(size_t id);
	
	public:
		Paquetes();
		void add_package(size_t id, string nombre_descriptivo, 
		size_t limite_paquete);
		void add_screws(size_t tipo_tornillo, size_t cant_tornillos, 
		size_t ancho_tornillos);
		void printf_remanentes();
		bool is_valid_screw(size_t id);
		~Paquetes();
};

#endif //PAQUETES_H
