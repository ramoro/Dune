#include "muerte.h"

std::shared_ptr<Estado> Muerte::actualizar(UnidadMovible *unidad,
Mapa &mapa, double tiempo_transcurrido) {
	unidad->serializar_mensaje_muerte();
	//std::vector<ObjetoDune*> unidad->ataque_al_morir();
	return NULL;
}