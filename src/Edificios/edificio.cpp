#include "edificio.h"

Edificio::Edificio(int costo_dinero, int gasto_energetico,
std::pair<int, int> dimension, int puntos_estructura, int id, 
int id_duenio, int base, int altura, std::pair<int, int> centro) :
ObjetoDune(puntos_estructura, costo_dinero, id, id_duenio, base, altura,
centro), gasto_energetico(gasto_energetico), dimension(dimension) {}