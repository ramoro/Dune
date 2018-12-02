#include "movimiento_para_atacar.h"
#include "ataque.h"
#include "inactividad.h"
#include <iostream>

MovimientoParaAtacar::MovimientoParaAtacar(std::shared_ptr<ObjetoDune>
objetivo): objeto_destino(objetivo), pos_destino(objetivo->obtener_centro()) {
	nombre = "mov para atacar";
}

std::shared_ptr<Estado> MovimientoParaAtacar::actualizar(UnidadMovible 
*unidad, Mapa &mapa, int tiempo_transcurrido) {
	//si la unidad ya esta muerta la unidad queda inactiva
	if (objeto_destino->esta_fuera_de_juego()) {
		unidad->limpiar_camino();
		std::shared_ptr<Inactividad> inactividad(new Inactividad());
		return inactividad;
	}
	//me fijo si la posicion de destino es diferente a la de la unidad
	//a atacar. En ese caso hay que recalcular el A*
	if (mapa.de_pixel_a_baldosa(pos_destino) != 
		mapa.de_pixel_a_baldosa(objeto_destino->obtener_centro())) {
		unidad->asignar_nuevo_camino(mapa.
		obtener_camino(unidad->obtener_centro(),
			objeto_destino->obtener_centro(),unidad));
		pos_destino = objeto_destino->obtener_centro();
	}
	Movimiento::actualizar(unidad, mapa, tiempo_transcurrido);
	std::pair<int, int> cercania = mapa.pedir_cercania(unidad->pedir_id(), 
	objeto_destino->pedir_id());
	if (cercania.first > unidad->obtener_rango_ataque() || 
	cercania.second > unidad->obtener_rango_ataque()) {
		return NULL;
	}
	unidad->limpiar_camino();
	std::shared_ptr<Ataque> ataque(new Ataque(objeto_destino));
	unidad->serializar_mensaje_ataque(objeto_destino->pedir_id());
	return ataque;
}