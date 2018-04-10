#ifndef PAQUETE_TORNILLOS_H
#define PAQUETE_TORNILLOS_H

#include <cstddef>
#include <iostream>
using namespace std;

Paquete_Tornillos (string id_tornillo, size_t capacidad_paquete);
void agregar_tornillo (size_t ancho_tornillo);
size_t get_capacidad ();	
size_t get_tornillos_dentro ();
string get_id_paquete ();
bool esta_lleno ();
int get_mediana ();


#endif //PAQUETE_TORNILLOS_H
