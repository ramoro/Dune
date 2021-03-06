#ifndef UNIDAD_MOVIBLE_H
#define UNIDAD_MOVIBLE_H

#include "../objeto_dune.h"
#include "../Armas/arma.h"
#include "../jugador.h"
#include "../mapa.h"
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <list>

class Estado;

/*Clase abstracta que representa una unidad movible en el mundo de Dune
que puede ser tanto un vehiculo como una unidad de infanteria.*/
class UnidadMovible: public ObjetoDune {
	private:
		int rango;
		int velocidad; //en km/h
		int tiempo_creacion; //en milisegundos
		std::list<std::pair<int, int>> camino; //esto deberia ser un vector de BALDOSAS
		
	protected:
		std::vector<Arma> armas;
		std::vector<int> ids_tipos_edificios_necesarios;
		std::vector<int> casa;
		std::shared_ptr<Estado> estado;
		int tiempo_acumulado;

	public:
		/*Constructor de la clase.*/
		UnidadMovible(int rango, int velocidad, 
		double tiempo_creacion, int costo_dinero, int vida, 
		int id, int id_duenio, int base, int altura, std::pair<int, int> 
		centro);

		/*Setea a 0 el tiempo acumulado*/
		void resetear_tiempo_acumulado();

		/*Sumo el tiempo recibido por parametro en el atributo*/
		void acumular_tiempo(int tiempo_transcurrido);

		/*Devuelve el tiempo acumulado por la unidad*/
		int obtener_tiempo_acumulado();

		/*Recibe un string con el objetivo al que esta atacando
		la unidad y el tiempo transcurrido en el juego y devuelve el danio
		que le realiza al objetivo. Devolvera 0 si no paso el tiempo
		suficiente que cumpla la frecuencia de disparo del arma con la
		que se ataca.*/
		int pedir_danio(std::string objetivo, int tiempo_transcurrido);
		
		int pedir_danio_explosion(std::string objetivo);

		/*Recibe el mapa del juego y
		el id del objeto a atacar. Devuelve un vector con los
		objetos a los que afecta.*/ 
		virtual std::vector<ObjetoDune*> atacar_objetivo(Mapa &mapa, 
		int id_objetivo) = 0;

		/*Metodo virtual puro que dania a la unidad apuntada por el puntero
		recibido.*/
		virtual int daniar(std::shared_ptr<UnidadMovible> unidad_atacante);

		/*Metodo virtual puro que mata a la unidad movible seteandola
		como muerta.*/
		virtual void matar();

		/*Devuelve el la posicion del centro del objeto.*/
		virtual std::pair<int, int> obtener_esquina();

		/*Metodo virtual puro que devuelve un vector de punteros a objetos
		afectados por la muerte de la unidad.*/
		virtual std::vector<ObjetoDune*> ataque_al_morir(Mapa &mapa) = 0;

		//virtual std::vector<int> matar(Mapa &mapa, Root &root) = 0;

		/*Le asigna a la unidad el estado de muerta.*/
		void poner_estado_muerta();

		/*Devuelve un vector con ids de los tipos de edificios que necesita
		la unidad para poder ser creada.*/
		std::vector<int> obtener_edificios_necesarios();

		/*Devuelve el rango de ataque filas o la cantidad de espacios
		de forma horizontal hasta donde se extiende el rango de vision
		de la unidad.*/
		int obtener_rango_ataque();

		/*Devuelve la velocidad de la unidad*/
		double obtener_velocidad(int tipo_terreno);

		/*Recibe el jugador duenio de la unidad y devuelve true si se puede
		agregar la nueva unidad al jugador. False en caso contrario.*/
		bool se_puede_agregar(Jugador &jugador); 

		/*Recibe el mapa del juego y agrega la nueva unidad al juego.*/
		void agregar(Mapa &mapa);

		/*Recibe una cantidad de milisegundos y se la disminuye 
		al tiempo de creacion. Devuelve el tiempo de creacion
		faltante para crear la unidad luego de haber disminuido los
		segundos recibidos.*/
		int tiempo_creacion_faltante(int milisegs);

		/*Le asigna el camino a seguir a la unidad y setea su estado
		en movimiento.*/
		void empezar_a_mover(Mapa &mapa, std::pair<int, int> 
		pos_destino);

		/*Recibe el tiempo transcurrido y el mapa del juego
		y segun el estado en el que se encuentre le objeto lo actualiza.*/
		void actualizar_unidad(int tiempo_transcurrido, 
		Mapa &mapa);

		/*Devuelve la lista de posiciones que debe recorrer la unidad
		para llegar a la posicion de destino. Para ello la unidad
		debe estar en movimiento. Sino se devolvera una lista vacia. */
		std::list<std::pair<int, int>> pedir_camino();

		/*Saca la primera posicion del camino armado para la unidad, indicando
		que avanzo a esa posicion.*/
		void avanzar_camino();

		/*Recibe un camino de posiciones y se lo asgina a la unidad.*/
		void asignar_nuevo_camino(std::list<std::pair<int, int>>
		nuevo_camino);

		/*Recibe el mapa del juego y un puntero al objeto atacado.
		Segun la distancia al objeto atacar se setea a la unidad en estado
		de ataque o en movimiento para ir a atacar.*/
		void iniciar_ataque(Mapa &mapa, std::shared_ptr<ObjetoDune> objetivo);

		/* Se agrega la accion unidad recien movida y los parametros 
		adjuntos a la misma segun el protocolo a la clase 
		MensajeProtocolo de la unidad.*/
		void serializar_mensaje_movimiento();

		/*Se agrega la accion terminar ataque y los parametros 
		adjuntos a la misma segun el protocolo a la clase 
		MensajeProtocolo de la unidad.*/
		void serializar_mensaje_termino_ataque(); 

		/*Se agrega la accion de ataque ejecutada por la unidad dentro 
		del juego y los parametros adjuntos a la 
		misma segun el protocolo a la clase MensajeProtocolo de la unidad.*/
		void serializar_mensaje_ataque(int id_unidad_atacada);

		/*Se agrega dentro de la clase ObjetoDune la accion 
		muerte de la unidad dentro del juego y los parametros adjuntos a la 
		misma segun el protocolo a la clase MensajeProtocolo de la unidad.*/
		void serializar_mensaje_muerte();

		/*Elimina todas las posiciones de la lista camino.*/
		void limpiar_camino();

		/*Se fija si el terreno pasado por parametro es valido para
		esta unidad*/
		virtual bool es_terreno_valido(int terreno) = 0;

		/*Devuelve un vector indicando a que casas pertenece la unidad*/
		std::vector<int> obtener_casa();

		/*Recibe el terreno, el mapa y el tiempo que paso y afecta el terreno 
		donde se encuentra la unidad segun que haga la unidad.*/
		virtual void afectar_terreno(std::shared_ptr<ObjetoDune> terreno,
		Mapa &mapa, int tiempo_transcurrido);

		/*En caso de que a unidad lleve especia encima se saca
		tanta especia como puede depositar en un segundo.*/
		virtual int depositar_especia_en_segundo();
		
		virtual bool puede_atacar_aliado();

};

#endif 