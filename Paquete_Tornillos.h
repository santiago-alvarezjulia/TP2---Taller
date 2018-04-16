#ifndef PAQUETE_TORNILLOS_H
#define PAQUETE_TORNILLOS_H

#include <string>
#include <vector>
using std::string;

class Paquete_Tornillos {
	size_t id;
	string descriptive_name;
	size_t capacity;
	size_t screws_inside;
	std::vector<size_t> screws_width;
	bool is_full;
	
	public:
		Paquete_Tornillos(size_t id_screw, string descriptive_name, 
		size_t capacity);
		size_t add_screws(size_t screws_quantity, size_t width);
		size_t get_capacity() const;	
		size_t get_screws_inside() const;
		size_t get_id() const;
		string get_descriptive_name() const;
		bool is_package_full() const;
		size_t get_mediana() const;
		void printf_paquete_lleno();
		~Paquete_Tornillos();
};

#endif //PAQUETE_TORNILLOS_H
