#ifndef GUSANO_H
#define GUSANO_H

#include "mensaje_protocolo.h"
#include "config.h"
#include <utility>

/*Clase que representa un gusano que sale cada cierto tiempo
de manera aleatoria dentro del mundo Dune.*/
class Gusano {
	private:
		int dimension_alto;
		int dimension_ancho;
		int tiempo_salida; //en milisegundos
		int contador_salida;
		std::pair<int, int> centro_salida;
		MensajeProtocolo mensaje;

	public:
		/*Constructor de la clase.*/
		Gusano(Config &config);

		Gusano();

		/*Devuelve la dimension en altura que ocupa el gusano.*/
		int obtener_dimesion_alto();

		/*Devuelve la dimension en ancho que ocupa el gusano.*/
		int obtener_dimesion_ancho();

		/*Recibe el tiempo transcurrido dentro del juego y actualiza
		el tiempo de salida del gusano. En caso de que le toque
		salir se devuelve true. False en caso contrario.*/
		bool actualizar_salida(int tiempo_transcurrido);

		/*Se agrega la accion de salida del gusano hacia la superficie dentro 
		del juego y los parametros adjuntos a la 
		misma segun el protocolo a la clase MensajeProtocolo del gusano.*/
		void serializar_mensaje_salida();

		/*Recibe un nueva posicion para el centro de donde saldra el
		gusano y se lo asigna a su centro de salida.*/
		void asignar_centro(std::pair<int, int> nuevo_centro);
};

#endif 