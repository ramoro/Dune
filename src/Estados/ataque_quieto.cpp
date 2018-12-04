#include "ataque_quieto.h"
#include "inactividad.h"

AtaqueQuieto::AtaqueQuieto(ObjetoDune* objetivo): objetivo(objetivo) {}

std::shared_ptr<Estado> AtaqueQuieto::actualizar(UnidadMovible *unidad,
Mapa &mapa, int tiempo_transcurrido) {
	nombre = "ataque quieto";
	if (objetivo->esta_fuera_de_juego()){
		//std::cout << "Ataque::actualizar esta muerta " << std::endl;
		unidad->serializar_mensaje_termino_ataque();
		std::shared_ptr<Inactividad> inactividad (new Inactividad());
		return inactividad;		
	}

	//Me fijo si esta lo suficientemente cerca
	std::pair<int, int> cercania = mapa.pedir_cercania(unidad->pedir_id(), 
	objetivo->pedir_id());
	// "Ataque::actualizar cercania "<< cercania.first << '-' << cercania.second << std::endl;
	if (cercania.first > unidad->obtener_rango_ataque() 
	|| cercania.second > unidad->obtener_rango_ataque()) {
		unidad->serializar_mensaje_termino_ataque();
		std::shared_ptr<Inactividad> inactividad (new Inactividad());
		return inactividad;		
	} else {
		int vida_restante = objetivo->daniar(unidad,
		tiempo_transcurrido);
		if (vida_restante <= 0) {
			objetivo->matar();
			unidad->serializar_mensaje_termino_ataque();
			std::shared_ptr<Inactividad> inactividad (new Inactividad());
			return inactividad;	
		}
	}
	return NULL;
}