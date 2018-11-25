#include "deposito.h"
#include "inactividad.h"
#include "movimiento_para_atacar.h"

#define SEGUNDO_EN_MILIS 1000

Deposito::Deposito(Refineria* objetivo, 
std::shared_ptr<ObjetoDune> coord): refineria_deposito(objetivo),
especia_a_volver(coord) {
	nombre = "deposito";
}

std::shared_ptr<Estado> Deposito::actualizar(UnidadMovible 
*unidad, Mapa &mapa, int tiempo_transcurrido) {
	contador_segundo += tiempo_transcurrido;
	if (tiempo_transcurrido >= SEGUNDO_EN_MILIS) {
		contador_segundo -= SEGUNDO_EN_MILIS;
		int especia_depositada = unidad->depositar_especia_en_segundo();
		if (especia_depositada == 0) {
			if (especia_a_volver->esta_fuera_de_juego()) {
				std::shared_ptr<Inactividad> inactividad(new Inactividad());
				return inactividad;
			} else {
				unidad->asignar_nuevo_camino(mapa.obtener_camino(
				unidad->obtener_centro(), especia_a_volver->obtener_centro()));
				std::shared_ptr<MovimientoParaAtacar> 
				movimiento_ataque_especia(new 
				MovimientoParaAtacar(especia_a_volver));
				return movimiento_ataque_especia;
			}
		}
		refineria_deposito->agregar_especia(especia_depositada);
	}
	return NULL;
}