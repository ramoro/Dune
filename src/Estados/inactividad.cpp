#include "inactividad.h"	
#include "ataque_quieto.h"

std::shared_ptr<Estado> Inactividad::actualizar(UnidadMovible *unidad,
Mapa &mapa, int tiempo_transcurrido) {
	nombre = "inactividad";
	std::vector<ObjetoDune*> objetivo_alrededor = mapa.
	buscar_unidades_alrededor(unidad->obtener_centro(), 
	(unidad->obtener_altura() + 
	unidad->obtener_rango_ataque())*2, (unidad->obtener_base() + 
	unidad->obtener_rango_ataque())*2, false, true, 
	unidad->pedir_id_duenio(), false);

	if(!objetivo_alrededor.empty()) {
		std::shared_ptr<AtaqueQuieto> ataque_quieto(new AtaqueQuieto(
		objetivo_alrededor[0]));
		unidad->serializar_mensaje_ataque(objetivo_alrededor[0]->pedir_id());
		return ataque_quieto;
	}
	return NULL;
}