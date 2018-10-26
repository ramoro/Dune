#include "edificio.h"

Edificio::Edificio(int costo_dinero, int gasto_energetico,
std::pair<int, int> dimension, int puntos_estructura) :
ObjetoDune(puntos_estructura, costo_dinero), 
gasto_energetico(gasto_energetico), dimension(dimension) {}

void Edificio::asignar_id(int identificador_edificio) {
	id = identificador_edificio;
}