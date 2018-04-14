#ifndef PAQUETES_H
#define PAQUETES_H

#include <map>
#include "Paquete_Tornillos.h"

class Paquetes {
	std::map<string, Paquete_Tornillos> paquetes;
	
	public:
		Paquetes();
		void agregar_paquete(string id, std::string limite_paquete);
		void agregar_tornillos(string tipo_tornillo, size_t cant_tornillos, 
		size_t ancho_tornillos);
		~Paquetes();
};

#endif //PAQUETES_H
