#include "muerte.h"

std::shared_ptr<Estado> Muerte::actualizar(UnidadMovible *unidad,
Mapa &mapa, double tiempo_transcurrido) {
	nombre = "muerte";
	unidad->serializar_mensaje_muerte();
	std::vector<ObjetoDune*> unidades_afectadas = unidad->
	ataque_al_morir(mapa);
	for (std::vector<ObjetoDune*>::iterator it = 
	unidades_afectadas.begin(); it != unidades_afectadas.end(); ++it) {
		int vida_restante = (*it)->daniar(unidad);
		if (vida_restante <= 0) {
			(*it)->matar();
		}
		unidad->serializar_mensaje_ataque((*it)->pedir_id());
	}
	return NULL;
}