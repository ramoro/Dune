#include "ataque.h"
#include "movimiento_para_atacar.h"
#include "inactividad.h"
#include <iostream>

Ataque::Ataque(std::shared_ptr<ObjetoDune> objetivo): 
objeto_destino(objetivo), pos_a_atacar(objetivo->obtener_centro()) {
	nombre = "ataque";
}

std::shared_ptr<Estado> Ataque::actualizar(UnidadMovible *unidad,
Mapa &mapa, int tiempo_transcurrido) {

	//Primero me fijo si esta lo suficientemente cerca
	//si no lo esta se devuelve el estado moviendose para atacar
	std::pair<int, int> cercania = mapa.pedir_cercania(unidad->pedir_id(), 
	objeto_destino->pedir_id());
	if (cercania.first > unidad->obtener_rango_ataque() 
	|| cercania.second > unidad->obtener_rango_ataque()) {
			unidad->asignar_nuevo_camino(mapa.obtener_camino(unidad->
			obtener_centro(), objeto_destino->obtener_centro()));
			//unidad->serializar_mensaje_termino_ataque();
			std::shared_ptr<MovimientoParaAtacar> movimiento_ataque(new 
			MovimientoParaAtacar(objeto_destino));
			return movimiento_ataque;
	}

	std::vector<ObjetoDune*> unidades_afectadas = unidad->
	atacar_objetivo(mapa, objeto_destino->pedir_id());
	if (unidades_afectadas.empty()) {
		//significa que es la cosechadora la q ataco
		unidad->afectar_terreno(objeto_destino, mapa, tiempo_transcurrido);
	} 
	std::cout << "llego a ataque" << std::endl;
	for (std::vector<ObjetoDune*>::iterator it = 
	unidades_afectadas.begin(); it != unidades_afectadas.end(); ++it) {
		int vida_restante = (*it)->daniar(unidad, tiempo_transcurrido);
		if (vida_restante <= 0) {
			(*it)->matar();
			//en caso de matar al objeto que fue a atacar queda en estado
			//inactivo la unidad
			if (objeto_destino->pedir_id() == (*it)->pedir_id()) {
				std::shared_ptr<Inactividad> inactividad(new Inactividad());
				return inactividad;
			}
		}
	}
	return NULL;
}