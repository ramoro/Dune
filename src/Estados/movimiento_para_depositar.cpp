#include "movimiento_para_depositar.h"
#include "deposito.h"
#include <iostream>
#include <list>

#define DISTANCIA_DEPOSITO 40
MovimientoParaDepositar::MovimientoParaDepositar(Refineria*
objetivo, std::shared_ptr<ObjetoDune> terreno): refineria_destino(objetivo),
coordenada_a_volver(terreno) {
	nombre = "mov para depositar";
}

std::shared_ptr<Estado> MovimientoParaDepositar::actualizar(UnidadMovible 
*unidad, Mapa &mapa, int tiempo_transcurrido) {
	std::cout << "Estado::cambiar_a_movimiento_para_deposita" << std::endl;
	std::list<std::pair<int, int>> camino = mapa.obtener_camino(
	unidad->obtener_centro(), refineria_destino->obtener_centro(), unidad);
	unidad->asignar_nuevo_camino(camino);
	std::pair<int, int> cercania = mapa.pedir_cercania(unidad->pedir_id(), 
	refineria_destino->pedir_id());
	while (cercania.first > DISTANCIA_DEPOSITO ||
	 cercania.second > DISTANCIA_DEPOSITO){
		cercania = mapa.pedir_cercania(unidad->pedir_id(), 
		refineria_destino->pedir_id());
/*		std::cout << "unidad en " << unidad->obtener_centro().first << '-'<<unidad->obtener_centro().second << std::endl;
		std::cout << "refineria en " << refineria_destino->obtener_centro().first << '-'<<refineria_destino->obtener_centro().second << std::endl;
		std::cout << "MovimientoParaDepositar::cercania " << cercania.first << '-' << cercania.second << std::endl;
*/		Movimiento::actualizar(unidad, mapa, tiempo_transcurrido);
	}
	//unidad->limpiar_camino();
	std::shared_ptr<Deposito> deposito(new Deposito(refineria_destino,
	coordenada_a_volver));
	return deposito;
	
	return NULL;
}