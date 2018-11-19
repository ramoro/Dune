#include "inactividad.h"
#include <list>	

std::shared_ptr<Estado> Inactividad::actualizar(UnidadMovible *unidad,
Mapa &mapa, double tiempo_transcurrido) {
	nombre = "inactividad";
	std::vector<ObjetoDune*> objetivo_alrededor = mapa.
	buscar_unidades_alrededor(unidad->obtener_centro(), 
	(unidad->obtener_altura() + 
	unidad->obtener_rango_ataque())*2, (unidad->obtener_base() + 
	unidad->obtener_rango_ataque())*2, false, true, 
	unidad->pedir_id_duenio(), false);

	if(!objetivo_alrededor.empty()) {
		int vida_restante = objetivo_alrededor[0]->daniar(unidad);
		if (vida_restante <= 0) {
			//objetivo_alrededor[0]->matar();
		}
		unidad->serializar_mensaje_ataque(objetivo_alrededor[0]->pedir_id());
		//ACA NO SE SI DEVOLVER NUEVO ESTADO ATACANDOQUIETO O NO
	}
	return NULL;
}