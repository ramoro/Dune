#include "deposito.h"
#include "inactividad.h"
#include "movimiento_para_atacar.h"

#define SEGUNDO_EN_MILIS 1000

Deposito::Deposito(Refineria* objetivo, 
std::shared_ptr<ObjetoDune> coord): refineria_deposito(objetivo),
especia_a_volver(coord) {
	nombre = "deposito";
	contador_segundo = 0;
}

std::shared_ptr<Estado> Deposito::actualizar(UnidadMovible 
*unidad, Mapa &mapa, int tiempo_transcurrido) {
	contador_segundo += tiempo_transcurrido;
	if (contador_segundo >= SEGUNDO_EN_MILIS) {
		contador_segundo -= SEGUNDO_EN_MILIS;
		int especia_depositada = unidad->depositar_especia_en_segundo();
		//std::cout << "Deposito::actualizar especia_depositada "<< especia_depositada << std::endl;
		if (especia_depositada == 0) {
			if (especia_a_volver->esta_fuera_de_juego()) {
				//std::cout << "especia muerta,buscar nueva especia " << std::endl;
				std::shared_ptr<ObjetoDune> especia_nueva = mapa.obtener_especia_cercana(unidad);
				if (especia_nueva != NULL){
					//std::cout << "Encontre especia nueva,yendo atr " << std::endl;
					unidad->asignar_nuevo_camino(mapa.obtener_camino(
					unidad->obtener_centro(), especia_nueva->obtener_centro(),
					unidad));
					std::shared_ptr<MovimientoParaAtacar> 
					movimiento_ataque_especia(new 
					MovimientoParaAtacar(especia_nueva));
					return movimiento_ataque_especia;
				}
				//std::cout << "NO hay especia nueva cerca " << std::endl;
				std::shared_ptr<Inactividad> inactividad(new Inactividad());
				return inactividad;
			} else {
				//std::cout << "Deposito::actualizar a depositar " << std::endl;
				unidad->asignar_nuevo_camino(mapa.obtener_camino(
				unidad->obtener_centro(), especia_a_volver->obtener_centro(),
				unidad));
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