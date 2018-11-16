#include "inactividad.h"
#include <list>	

std::shared_ptr<Estado> Inactividad::actualizar(UnidadMovible *unidad,
Mapa &mapa, double tiempo_transcurrido) {
	std::vector<ObjetoDune*> objetivo_alrededor = mapa.
	buscar_unidades_alrededor(unidad->obtener_centro(), 
	unidad->obtener_altura() + 
	unidad->obtener_rango_ataque_columnas(), unidad->obtener_base() + 
	unidad->obtener_rango_ataque_filas(), false, true, 
	unidad->pedir_id_duenio());

	if(!objetivo_alrededor.empty()) {
		int vida_restante = objetivo_alrededor[0]->daniar();
		if (vida_restante <= 0) {
			//objetivo_alrededor[0]->matar();
		}
		unidad->serializar_mensaje_ataque(objetivo_alrededor[0]->pedir_id());
		//ACA NO SE SI DEVOLVER NUEVO ESTADO ATACANDOQUIETO O NO
	}
	return NULL;
}