#ifndef SCREW_PACKAGE_H
#define SCREW_PACKAGE_H

#include <string>
#include <vector>

class Screw_Package {
	size_t id;
	std::string descriptive_name;
	size_t capacity;
	size_t screws_inside;
	std::vector<size_t> screws_width;
	bool is_full;
	
	public:
		Screw_Package(size_t id_screw, std::string descriptive_name, 
		size_t capacity);
		size_t add_screws(size_t screws_quantity, size_t width);
		size_t get_capacity() const;	
		size_t get_screws_inside() const;
		size_t get_id() const;
		std::string get_descriptive_name() const;
		bool is_package_full() const;
		size_t get_mediana() const;
		void printf_paquete_lleno();
		~Screw_Package();
};

#endif //SCREW_PACKAGE_H
