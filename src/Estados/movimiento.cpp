#include "movimiento.h"
#include "inactividad.h"
#include <list>	
#include <iostream>
#include "math.h"

//VER CUANTO MOVER A LA UNIDAD SEGUN EL TIEMPO TRANSCURRIDO Y SU VELOCIDAD
std::shared_ptr<Estado> Movimiento::actualizar(UnidadMovible *unidad,
Mapa &mapa, int tiempo_transcurrido) {
	std::list<std::pair<int, int>> camino = unidad->pedir_camino();
	bool posicion_ocupada = mapa.esta_ocupada_coordenada(camino.front());
	if (posicion_ocupada && camino.size() == 1) {
		unidad->limpiar_camino();
		std::shared_ptr<Inactividad> inactividad(new Inactividad());
		return inactividad;
	} else if (posicion_ocupada) {
		camino = mapa.obtener_camino(unidad->obtener_centro(), camino.back());
		unidad->asignar_nuevo_camino(camino);
		//quizas se deberia tener en cuenta un super caso borde que no
		//se devuelva ningun camino
	}
	//en vez de front deberia ser la posicion segun el tiempo y la velocidad
	//a avanzar camino deberia pasarle la cantiadd de posiciones que avanzo ene l camino
	
#ifdef NACHO
	tiempo_transcurrido+=unidad->obtener_tiempo_acumulado();
	double dist1 = sqrt(abs(unidad->obtener_centro().first - camino.back().first) * abs(unidad->obtener_centro().second - camino.back().second));
	double dist2 = tiempo_transcurrido * unidad->obtener_velocidad();

	if (dist2 <= dist1){
		//mapa.mover_unidad(unidad->pedir_id(), camino.front());
		//unidad->avanzar_camino();
   		//unidad->serializar_mensaje_movimiento(); 
		unidad->acumular_tiempo(tiempo_transcurrido);
	} else {
		//for (int i = 0 ; i < dist1 ; i++){
			mapa.mover_unidad(unidad->pedir_id(), camino.front());
			unidad->avanzar_camino();
	   		unidad->serializar_mensaje_movimiento(); 
			if (camino.size() == 1) {
				std::shared_ptr<Inactividad> inactividad(new Inactividad());
				return inactividad;
			}
			unidad->resetear_tiempo_acumulado();
		//}
	}

/*
std::cout << "Tiene que esperar para moverse1" << std::endl;
float distance = sqrt(pow(camino.back().first-camino.front().first,2)+pow(camino.back().second-camino.front().second,2));
if (distance == 0){
	std::shared_ptr<Inactividad> inactividad(new Inactividad());
	return inactividad;	
}
float directionX = (camino.back().first-camino.front().first) / distance;
float directionY = (camino.back().second-camino.front().second) / distance;
mapa.mover_unidad(unidad->pedir_id(), camino.front());
std::cout << distance << "Tiene que esperar para moverse2" << std::endl;
//unidad->avanzar_camino();
//unidad->serializar_mensaje_movimiento(); 
bool moving = true;
// On update

if(moving == true)
{
	std::cout << "Tiene que esperar para moverse2.5" << std::endl;
	std::pair<int,int> cen(unidad->obtener_centro());
    cen.first += directionX * unidad->obtener_velocidad() * tiempo_transcurrido;
    	std::cout << directionX << "Tiene que esperar para moverse2.7" << tiempo_transcurrido << std::endl;

    cen.second += directionY * unidad->obtener_velocidad() * tiempo_transcurrido;
        	std::cout << "Tiene que esperar para moverse2.75" << std::endl;

    mapa.mover_unidad(unidad->pedir_id(), cen);
    	std::cout << "Tiene que esperar para moverse2.8" << std::endl;

    unidad->avanzar_camino();
    	std::cout << "Tiene que esperar para moverse2.9" << std::endl;

	unidad->serializar_mensaje_movimiento(); 

	std::cout << "Tiene que esperar para moverse3" << camino.front().first << std::endl;

    if(sqrt(pow(unidad->obtener_centro().first-camino.front().first,2)+pow(unidad->obtener_centro().second-camino.front().second,2)) >= distance)
    {
    	        std::cout << "Tiene que esperar para moverse3.2" << std::endl;

    	mapa.mover_unidad(unidad->pedir_id(), camino.back());
	    //unidad->avanzar_camino();
	            std::cout << "Tiene que esperar para moverse3.3" << std::endl;

    	unidad->serializar_mensaje_movimiento(); 
        moving = false;
        std::cout << "Tiene que esperar para moverse4" << std::endl;
    }


}*/

#endif
 
	//mapa.mover_unidad(unidad->pedir_id(), camino.front());

	//unidad->avanzar_camino();
   	//unidad->serializar_mensaje_movimiento(); 


	//significa que llego a destino, deberia cambiar la verificacion, ya que es segunc uanto se mueve
	//ademas de que porahi antes ya esta ocupado por un pedazo de edificio

	if (camino.size() == 1) {
		std::shared_ptr<Inactividad> inactividad(new Inactividad());
		return inactividad;
	}	

	return NULL;

}