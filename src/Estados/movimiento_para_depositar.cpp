#include "movimiento_para_depositar.h"
#include "deposito.h"
#include <iostream>
#include <list>

MovimientoParaDepositar::MovimientoParaDepositar(Refineria*
objetivo, std::shared_ptr<ObjetoDune> terreno): refineria_destino(objetivo),
coordenada_a_volver(terreno) {
	nombre = "mov para depositar";
}

std::shared_ptr<Estado> MovimientoParaDepositar::actualizar(UnidadMovible 
*unidad, Mapa &mapa, int tiempo_transcurrido) {
	std::list<std::pair<int, int>> camino = mapa.obtener_camino(
	unidad->obtener_centro(), refineria_destino->obtener_centro(), unidad);
	unidad->asignar_nuevo_camino(camino);
	if (Movimiento::actualizar(unidad, mapa, tiempo_transcurrido)) {
		unidad->limpiar_camino();
		std::shared_ptr<Deposito> deposito(new Deposito(refineria_destino,
		coordenada_a_volver));
		return deposito;
	}
	return NULL;
}