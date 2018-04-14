#ifndef PAQUETE_TORNILLOS_H
#define PAQUETE_TORNILLOS_H

#include <string>
#include <vector>
using std::string;

class Paquete_Tornillos {
	string id;
	size_t capacity;
	size_t screws_inside;
	std::vector<size_t> screws_width;
	bool is_full;
	
	public:
		Paquete_Tornillos(string id_screw, size_t capacity);
		void add_screws(size_t screws_quantity, size_t width);
		size_t get_capacity() const;	
		size_t get_screws_inside() const;
		string get_id() const;
		bool is_package_full() const;
		size_t get_mediana() const;
		~Paquete_Tornillos();
};

#endif //PAQUETE_TORNILLOS_H
