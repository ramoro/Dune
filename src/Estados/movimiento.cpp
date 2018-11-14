#include "movimiento.h"

std::shared_ptr<Estado> Movimiento::actualizar(UnidadMovible *unidad,
Mapa &mapa) {
	/*pido camino
	me fijo si la posicion a moverse esta ocupada
	en caso de ocupada vuelvo a calcular A*
	sino muevo la unidad a esa posicion sancandola de donde estaba en el mapa y ponindola en el nuevo lugar
	saco la posicion a la que avanzo del camino
	si llego a destino devuelvo otro estado (o NULL). 
	En caso de no devolver null se deberia luego serializar mensaje.*/
	return NULL;
}