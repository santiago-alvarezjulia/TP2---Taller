#ifndef PACKAGES_H
#define PACKAGES_H

#include "Screw_Package.h"
#include "Lock.h"
#include <map>
#include <string>
#include <mutex>

class Packages {
	std::map<size_t, Screw_Package> packages;
	std::map<size_t, std::mutex*> mutexes;
	void cambiar_paquete_lleno(size_t id);
	
	public:
		Packages();
		void add_package(size_t id, std::string nombre_descriptivo, 
		size_t limite_paquete);
		void add_screws(size_t id, size_t cant_tornillos, 
		size_t ancho_tornillos, std::string filename);
		void printf_remanentes();
		int is_valid_screw(size_t id, size_t cant_tornillos, 
		size_t ancho_tornillos);
		~Packages();
};

#endif //PACKAGES_H
