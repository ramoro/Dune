#include "movimiento.h"
#include "inactividad.h"
#include <list>	

//VER CUANTO MOVER A LA UNIDAD SEGUN EL TIEMPO TRANSCURRIDO Y SU VELOCIDAD
std::shared_ptr<Estado> Movimiento::actualizar(UnidadMovible *unidad,
Mapa &mapa, double tiempo_transcurrido) {
	std::list<std::pair<int, int>> camino = unidad->pedir_camino();
	bool posicion_ocupada = mapa.esta_ocupada_coordenada(camino.front());
	if (posicion_ocupada) {
		camino = mapa.obtener_camino(unidad->obtener_centro(), camino.back());
		unidad->asignar_nuevo_camino(camino);
		//quizas se deberia tener en cuenta un super caso borde que no
		//se devuelva ningun camino
	}
	//en vez de front deberia ser la posicion segun el tiempo y la velocidad
	//a avanzar camino deberia pasarle la cantiadd de posiciones que avanzo ene l camino
	mapa.mover_unidad(unidad->pedir_id(), camino.front());
	unidad->avanzar_camino();
	unidad->serializar_mensaje_movimiento(); 
	//significa que llego a destino, deberia cambiar la verificacion, ya que es segunc uanto se mueve
	if (camino.size() == 1) {
		std::shared_ptr<Inactividad> inactividad(new Inactividad());
		return inactividad;
	}	
	return NULL;
}