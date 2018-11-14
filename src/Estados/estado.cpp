#include "estado.h"
#include "movimiento.h"

std::shared_ptr<Estado> Estado::actualizar(UnidadMovible *unidad) {
	return NULL;
}

std::shared_ptr<Estado> Estado::cambiar_a_movimiento() {
	std::shared_ptr<Movimiento> movimiento(new Movimiento());
	return movimiento;
}